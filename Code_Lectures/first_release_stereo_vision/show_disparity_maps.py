# partially based on stereo_match.py example in the OpenCV distribution.
import glob
import numpy as np
import cv2
import pdb

def show_disparity_maps(image_set = 'middlebury'):
    # parameters for the stereo matching:
    window_size = 7;
    min_disp = 0;
    num_disp = 16; # must be divisible by 16 (http://docs.opencv.org/java/org/opencv/calib3d/StereoSGBM.html)
    
    if(image_set == 'middlebury'):
        
        imgL = cv2.imread('./middlebury/im2.png');
        imgR = cv2.imread('./middlebury/im6.png');
        
         # calculate the disparities:
        num_disp = 64;
        disp = calculate_disparities(imgL, imgR, window_size, min_disp, num_disp);
        # show the output
        show_disparity_map(imgL, imgR, disp, min_disp, num_disp);
    else:
        im_files = glob.glob("./" + image_set + "/*.bmp");
        
        # iterate over the files:
        for im in im_files:
            # read the image (consisting of a right image and left image)
            cv_im = cv2.imread(im);
            imgL = cv_im[0:96, 126:252, :];
            imgR = cv_im[0:96, 0:126, :];
            # calculate the disparities:
            disp = calculate_disparities(imgL, imgR, window_size, min_disp, num_disp);
            # show the output
            show_disparity_map(imgL, imgR, disp, min_disp, num_disp);
            
def show_disparity_map(imgL, imgR, disp, min_disp, num_disp):		
    # show the output
    cv2.imshow('left', imgL);
    cv2.imshow('right', imgR);
    cv2.imshow('disparity', (disp-min_disp)/num_disp);
    		
    # wait for a key to be pressed before moving on:
    cv2.waitKey();
    cv2.destroyAllWindows();

def calculate_disparities(imgL, imgR, window_size, min_disp, num_disp):
    # semi-global matching:
    stereo = cv2.StereoSGBM_create(numDisparities = num_disp, blockSize = window_size);
    disp = stereo.compute(imgL, imgR).astype(np.float32) / 16.0;
    return disp; 
	
show_disparity_maps(image_set = 'pole'); # other options: 'race', 'pole', 'middlebury'    