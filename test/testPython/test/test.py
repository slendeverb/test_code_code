from typing import Any
import torch
import numpy as np
import torch.nn as nn
from torch.utils.data import Dataset
import cv2
from PIL import Image
import os

def compute_error_for_line_given_points(b,w,points):
    totalError=0
    for i in range(0,len(points)):
        x=points[i,0]
        y=points[i,1]
        totalError+=(y-(w*x+b))**2
    return totalError/float(len(points))

