import numpy as np
import cv2

# Contrast Boost
img = cv2.imread('./BM3D_Image/out.pgm',0)
# Applying CLAHE model
clahe = cv2.createCLAHE(clipLimit=3.5, tileGridSize=(4,4))
cl1 = clahe.apply(img)
cv2.imwrite('./Contrast_Enhanced_Image/out.pgm',cl1)
# Application of SIFT
sift = cv2.SIFT()
kp = sift.detect(gray,None)
img=cv2.drawKeypoints(cl1,kp)
cv2.imwrite('./SIFT/out.pgm',img_out)
