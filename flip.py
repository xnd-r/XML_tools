#! /usr/bin/python2

import cv2
from sys import argv

for f in argv[1:]:
	img = cv2.imread(f)
	img = cv2.flip(img, 1)
	cv2.imwrite(f,img)
