# Filename e:TraverseTest.py
""" Traverse test """

__version__ = "0.1"

import glob as gb


# import  cv2

# Returns a list of all folders with participant numbers
def CvImage():
    img_path = gb.glob("D:/test/*/*.jpg")
    for path in img_path:
        print(path);
        # img = cv2.imread(path)
        # cv2.imshow('img', img)
        # cv2.waitKey(1000)

# CvImage();
