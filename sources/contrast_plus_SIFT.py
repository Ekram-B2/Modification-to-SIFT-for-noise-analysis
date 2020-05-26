import numpy as np
import cv2
import itertools
import sys

print cv2.__version__
img = cv2.imread('./BM3D_Image/out.pgm',0)
print(sys.argv[1])
img_original = cv2.imread(sys.argv[1],0)
# Applying contrast accentuation
equ = cv2.equalizeHist(img)
cv2.imwrite('./Contrast_Enhanced_Image/out.pgm',equ)

# Applying SIFT
detector = cv2.FeatureDetector_create("SIFT")
descriptor = cv2.DescriptorExtractor_create("SIFT")
skp_1 = detector.detect(equ)
skp_2 = detector.detect(img_original)

# Print number of keypoint per image	
print('Number of keypoints in agumented image is {}'.format(len(skp_1)))
print('Number of keypoints in original image is {}'.format(len(skp_2)))

# Drawing keypoints to image
img_2 = cv2.drawKeypoints(img,skp_1,flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
# Showing agumented image
cv2.imshow("Keypoints",img_2)
cv2.waitKey(0)
cv2.imwrite('./SIFT_Image/out.pgm',img_2)
