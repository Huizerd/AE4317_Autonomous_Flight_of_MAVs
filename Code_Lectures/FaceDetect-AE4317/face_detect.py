"""

Code from https://github.com/shantnu/FaceDetect/
Adapted for the course AE4317

"""
import cv2
import sys
import cProfile
import pstats

def run_face_detector(imagePath = "abba.png", cascPath = "haarcascade_frontalface_default.xml", graphics = False):
    
    # Create the haar cascade
    faceCascade = cv2.CascadeClassifier(cascPath)
    
    # Read the image
    image = cv2.imread(imagePath)
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    
    # Detect faces in the image
    faces = faceCascade.detectMultiScale(
        gray,
        scaleFactor=1.1,
        minNeighbors=5,
        minSize=(30, 30),
        maxSize=(90,90),
        flags = cv2.CASCADE_SCALE_IMAGE
    )
    
    print("Found {0} faces!".format(len(faces)))
    
    if(graphics):
        # Draw a rectangle around the faces
        for (x, y, w, h) in faces:
            cv2.rectangle(image, (x, y), (x+w, y+h), (0, 255, 0), 2)
        
        cv2.imshow("Faces found", image)
        cv2.waitKey(0)

run_face_detector(graphics=True);

cProfile.run('run_face_detector()', 'restats');
p = pstats.Stats('restats')
p.sort_stats('cumulative').print_stats(10)