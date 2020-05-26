import sys
import numpy as np
import pybm3d
import scipy.ndimage
from PIL import Image

for i in range(16):
	basename = 'IMG_'
	extension = '.pgm'
	abs_path = './Images/IMG_' + str(i + 1) + '.pgm'
	print(abs_path)
	noise_std_dev = 40
	img = scipy.ndimage.imread(abs_path)
	out = pybm3d.bm3d.bm3d(img, noise_std_dev)
	im = Image.fromarray(out)
	im.save("./Denoised_Images/Denoised_Im_" + str(i + 1 ) + '.pgm')

