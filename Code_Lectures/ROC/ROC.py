# -*- coding: utf-8 -*-
"""
Created on Wed Feb 28 12:40:14 2018

Generating an ROC curve.

@author: LocalAdmin
"""

import cv2
import matplotlib.pyplot as plt
import numpy as np

def get_ROC_curve_naive(values, classes):
    """ Naive implementation of a ROC curve generator that iterates over a number of thresholds. 
    """
    
    # get number of positives and negatives:    
    n_values = len(values);
    totalP = len(np.where(classes > 0)[0]);
    totalN = n_values - totalP;
    
    min_val = np.min(values);
    max_val = np.max(values);
    thresholds = np.arange(min_val, max_val, 1.0);
    n_thresholds = len(thresholds);
    
    TP = np.zeros([n_thresholds, 1]);
    FP = np.zeros([n_thresholds, 1]);

    for t in range(n_thresholds):
        inds = np.where(values >= thresholds[t]);
        P = np.sum(classes[inds[0]]);
        TP[t] = P / totalP;
        F = len(inds[0]) - P;
        FP[t] = F / totalN;
    
    return TP, FP;

def get_ROC_curve(values, classes):
    """ Implementation of a ROC curve generator that only uses thresholds at the sample values.
    """
    
    # get number of positives and negatives:    
    n_values = len(values);
    totalP = len(np.where(classes > 0)[0]);
    totalN = n_values - totalP;
    
    # sort all values:
    inds = np.argsort(values);
    s_values = values[inds];
    s_classes = classes[inds];

    # the generator should only test for a given threshold value once
    # so we need to take into account duplicates:
    n_unique = len(np.unique(s_values));
    TP = np.zeros([n_unique, 1]);
    FP = np.zeros([n_unique, 1]);

    ind = 0;
    for e in range(n_values):
        # only determine the FP and TP value if the threshold has not been tested before:
        if(e == 0 or s_values[e-1] != s_values[e]):
            # threshold = s_values[e]
            # Positive when bigger:
            P = np.sum(s_classes[e:]);
            TP[ind] = P / totalP;
            
            # number of false positives is the remaining samples above the
            # threshold divided by all negative samples:
            FP[ind] = (len(s_classes[e:]) - P) / totalN;
            ind += 1

    return TP, FP;


def ROC_exercise(im_name, segmentation_name, show_images = False):
    """ Generate a ROC curve for a binary sky classification task
    """
        
    # read RGB image:
    Im = cv2.imread(im_name);
    WIDTH = Im.shape[1];
    HEIGHT = Im.shape[0];
    if(show_images):
        cv2.imshow('Image', Im);
        cv2.waitKey();
    
    # read Classification image:
    Cl = cv2.imread(segmentation_name);
    if(show_images):
        cv2.imshow('Segmentation', Cl);
        cv2.waitKey();
    Cl = cv2.cvtColor(Cl, cv2.COLOR_BGR2GRAY);
    Cl = Cl.flatten();
    Cl = Cl > 0;
    Cl = Cl.astype(float);
    
    # make a meshgrid:
    x, y = np.meshgrid(range(WIDTH), range(HEIGHT));
    x = x.flatten();
    y = y.flatten();
    
    # take the blue channel, cv2 represents images as BGR:
    # TODO: play with the next expression:
    Values = Im[:,:,0]; #-y #Im[:,:,2];
    Values = Values.flatten();

    # get the ROC curve:
    TP, FP = get_ROC_curve_naive(Values, Cl);
    # TP, FP = get_ROC_curve(Values, Cl);
    
    plt.figure();
    plt.plot(FP, TP, 'b');
    plt.xlabel('TP');
    plt.ylabel('FP');


im_name = 'CroppedImage.bmp';
segmentation_name = 'TreeSegmentation.bmp';
ROC_exercise(im_name, segmentation_name);
