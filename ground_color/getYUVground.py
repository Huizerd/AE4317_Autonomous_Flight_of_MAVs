# Function to detect the thresholds needed for correct ground detection
# in the cyberzoo. Resulting thresholds are in YUV.

import cv2
import numpy as np
import sys



def loadImage(fileName):

  image = cv2.imread(fileName, cv2.IMREAD_COLOR)

  if image is None:
    raise Exception('Could not load image!')

  # r, c  = image.shape[:2]
  # M     = cv2.getRotationMatrix2D((c/2, r/2), -90, 1)
  # image = cv2.warpAffine(image, M, (c, r))

  return image



def showImage(image, windowName='Image'):

  cv2.imshow(windowName, image)

  k = cv2.waitKey(0)
  if k == 27:         # wait for ESC key to exit
    cv2.destroyAllWindows()

  return



def RGBtoYUV(image):

  return cv2.cvtColor(image, cv2.COLOR_BGR2YUV)



if __name__ == '__main__':

  fileName = sys.argv[1]

  image    = loadImage(fileName)
  imageYUV = RGBtoYUV(image)

  showImage(image, windowName='RGB')
  showImage(image, windowName='YUV')

  print('BGR: 80, 90, 90')
  YUV = np.uint8([[[90, 90, 80]]])
  print('YUV:', cv2.cvtColor(YUV, cv2.COLOR_BGR2YUV))
