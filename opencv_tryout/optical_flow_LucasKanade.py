import sys
import numpy as np
import cv2

cap = cv2.VideoCapture(sys.argv[1])

if not cap.isOpened(): 
    raise Exception("Could not load video!")

# params for ShiTomasi corner detection
feature_params = dict( maxCorners = 100,
                       qualityLevel = 0.3,
                       minDistance = 7,
                       blockSize = 7 )

# Parameters for lucas kanade optical flow
lk_params = dict( winSize  = (15,15),
                  maxLevel = 2,
                  criteria = (cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT, 10, 0.03))

# Create some random colors
color = np.random.randint(0,255,(100,3))

# Take first frame and find corners in it
ret, old_frame = cap.read()

old_gray = cv2.cvtColor(old_frame, cv2.COLOR_BGR2GRAY)
p0 = cv2.goodFeaturesToTrack(old_gray, mask = None, **feature_params)

# Create a mask image for drawing purposes
mask = np.zeros_like(old_frame)

FoE = [0.0, 0.0]

while(1):
    ret,frame = cap.read()
    frame_gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Calculate optical flow
    p1, st, err = cv2.calcOpticalFlowPyrLK(old_gray, frame_gray, p0, None, **lk_params)

    # Select good points
    good_new = p1[st==1]
    good_old = p0[st==1]

    flow_vec = good_new - good_old

    n_points = p0.shape[0]
    sample_size = 3 # minimal sample size

    if n_points >= sample_size:

        # Estimate linear flow field for horizontal and vertical flow separately
        # Make a big matrix A with elements [x, y, 1]
        A = np.concatenate((good_old, np.ones([good_old.shape[0], 1])), axis=1)
        A_inv = np.linalg.pinv(A) # pseudo-inverse

        # Target = horizontal flow
        u_vec  = flow_vec[:, 0]
        pu     = np.dot(A_inv, u_vec)
        errs_u = np.abs(np.dot(A, pu) - u_vec) # least-squares error

        # Target = vertical flow
        v_vec  = flow_vec[:, 1]
        pv     = np.dot(A_inv, v_vec)
        errs_v = np.abs(np.dot(A, pv) - v_vec)

        err = (np.mean(errs_u) + np.mean(errs_v)) / 2.

    else:
        # not enough samples to make a linear fit:
        pu = np.asarray([0.0]*3);
        pv = np.asarray([0.0]*3);
        err = 10.;

    # The flow planes intersect the flow = 0 plane in a line
    # The FoE is the point where these 2 lines intersect (flow = (0, 0))
    FoE[0] = (pu[2] * pv[1] - pv[2] * pu[1]) / (pv[0] * pu[1] - pu[0] * pu[1]);
    FoE[1] = (-pu[0] * FoE[0] + pu[2]) / (pu[1]);
    divergence = (pu[0] + pv[1]) / 2.; # divide by 2 or not?

    print('error = {}, FoE = {}, {}, and divergence = {}'.format(err, FoE[0], FoE[1], divergence))

    # draw the tracks
    for i,(new,old) in enumerate(zip(good_new,good_old)):
        a,b = new.ravel()
        c,d = old.ravel()
        mask = cv2.line(mask, (a,b),(c,d), color[i].tolist(), 2)
        frame = cv2.circle(frame,(a,b),5,color[i].tolist(),-1)
    img = cv2.add(frame,mask)

    cv2.imshow("frame",img)
    k = cv2.waitKey(30) & 0xff
    if k == 27:
        break

    # Now update the previous frame and previous points
    old_gray = frame_gray.copy()
    p0 = good_new.reshape(-1,1,2)

cv2.destroyAllWindows()
cap.release()