import cv2
import numpy as np
import matplotlib.pyplot as plt

cap = cv2.VideoCapture("Bebop_color_movinghand.avi")
ret, frame1 = cap.read()

prvs = cv2.cvtColor(frame1, cv2.COLOR_BGR2GRAY)
hsv = np.zeros_like(frame1)

# Quiver locations
X, Y = np.mgrid[0:frame1.shape[0], 0:frame1.shape[1]]

hsv[..., 1] = 255 # ... (Ellipsis) places as many : as needed to select all dimensions

while True:

    ret, frame2 = cap.read()

    nxt  = cv2.cvtColor(frame2, cv2.COLOR_BGR2GRAY)
    flow = cv2.calcOpticalFlowFarneback(prvs, nxt, None, 0.5, 3, 15, 3, 5, 1.2, 0)

    # For quiver
    U = flow[..., 0]
    V = flow[..., 1]

    # plot = plt.figure()

    # plt.quiver(X, Y, U, V, alpha=.5)
    # plt.quiver(X, Y, U, V, edgecolor='k', facecolor='None', linewidth=.5)
    # plt.show(plot)

    mag, ang = cv2.cartToPolar(flow[..., 0], flow[..., 1])

    hsv[..., 0] = ang * 180 / np.pi / 2
    hsv[..., 2] = cv2.normalize(mag, None, 0, 255, cv2.NORM_MINMAX)

    bgr = cv2.cvtColor(hsv, cv2.COLOR_HSV2BGR)

    cv2.imshow("frame2", bgr)

    k = cv2.waitKey(30) & 0xff # to select only the last 8 bits

    if k == 27:
        break
    elif k == ord("s"):
        cv2.imwrite("opticalfb.png", frame2)
        cv2.imwrite("opticalhsv.png", bgr)

    prvs = nxt

cap.release()
cv2.destroyAllWindows()