# Based on a paper by Mori and Scherer: First Results in Detecting and Avoiding
# Frontal Obstacles from a Monocular Camera for MAVs
#
# Author: Jesse Hagenaars, 12-03-2018

import cv2
import numpy as np
import matplotlib.pyplot as plt



def loadCapture(path):
  """
  This function loads the video found at the given path. Raises exception
  in case no video was found, or the function was unable to open it.
  """

  capture = cv2.VideoCapture(path)

  if not capture.isOpened(): 
    raise Exception("Could not load video!")

  return capture



def getKeypoints(prevFrame, currFrame, method='ORB'):
  """
  This function obtains keypoints from consecutive frames using a specified
  method.
  """

  # Use U-SURF instead of surf since orientation is not important?
  if method is 'SURF':
    
    # Create SURF object, set threshold for Hessian
    # Common value is 300-500
    hessianThreshold = 300
    detector = cv2.xfeatures2d.SURF_create(hessianThreshold)

    # Find keypoints and descriptors for both frames
    prevKeypoints, prevDescriptors = detector.detectAndCompute(prevFrame, None)
    currKeypoints, currDescriptors = detector.detectAndCompute(currFrame, None)

  elif method is 'ORB':

    # Create ORB detector
    detector = cv2.ORB_create()

    # Find keypoints and descriptors for both frames
    prevKeypoints, prevDescriptors = detector.detectAndCompute(prevFrame, None)
    currKeypoints, currDescriptors = detector.detectAndCompute(currFrame, None)

  return detector, prevKeypoints, prevDescriptors, currKeypoints, currDescriptors



def matchKeypoints(prevDescriptors, currDescriptors, amount=10):
  """
  This function matches keypoints from consecutive frames using brute-force
  matching.
  """

  # Create brute-force matcher based on Hamming distance
  bfm = cv2.BFMatcher(cv2.NORM_HAMMING, crossCheck=True)

  # Match descriptors and sort in order of distance, return first amount
  matches = bfm.match(prevDescriptors, currDescriptors)
  matches = sorted(matches, key=lambda x:x.distance)[:amount]

  return matches



def draw(prevFrame, prevKeypoints, currFrame=None, currKeypoints=None, matches=None, method='keypoints', color=(255, 0, 0), flag=2):
  """
  This function draws either the keypoints for 1 frame, or the matching
  keypoints between 2 frames. Flag: 2 for ..., 4 for rich keypoints.
  """

  if method is 'keypoints':

    drawing = cv2.drawKeypoints(prevFrame, prevKeypoints, color, flag)

  elif method is 'matches' and currFrame is not None and currKeypoints is not None and matches is not None:

    drawing = cv2.drawMatches(prevFrame, prevKeypoints, currFrame, currKeypoints, matches, color, flag)

  cv2.imshow('Frame', drawing)

  return drawing



if __name__ == '__main__':

  capture = loadCapture('Bebop_color_movinghand.avi')

  # Get first frame
  success, prevFrame = capture.read()

  # Convert to grayscale
  prevFrame_gray = cv2.cvtColor(prevFrame, cv2.COLOR_BGR2GRAY)

  while True:

    # Read next frame
    success, currFrame = capture.read()

    # Convert to grayscale
    currFrame_gray = cv2.cvtColor(currFrame, cv2.COLOR_BGR2GRAY)

    # Obtain keypoints with ORB
    detector, prevKeypoints, prevDescriptors, currKeypoints, currDescriptors = getKeypoints(prevFrame_gray, currFrame_gray, method='ORB')

    # Match between frames, only 10 best matches
    matches = matchKeypoints(prevDescriptors, currDescriptors, amount=20)

    # Draw matches
    drawing = draw(prevFrame_gray, prevKeypoints, currFrame_gray, currKeypoints, matches, method='matches', flag=4)

    # Lag between frames
    k = cv2.waitKey(50) & 0xff # to select only the last 8 bits

    if k == 27:
        break
    elif k == ord('s'):
        cv2.imwrite('keypoints.png', drawing)
        cv2.imwrite('frame.png', currFrame_gray)

    # Set current as previous and 'crawl' forward
    prevFrame_gray = currFrame_gray

# Close all
capture.release()
cv2.destroyAllWindows()