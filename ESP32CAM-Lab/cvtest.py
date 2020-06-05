import cv2
import numpy as np
jpg = cv2.imread("dog.jpg",0)
cv2.imshow("Dog",jpg)
cv2.waitKey(0)
cv2.destroyAllWindows()
