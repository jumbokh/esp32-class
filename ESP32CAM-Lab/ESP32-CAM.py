#ESP32CAM請使用本程式：https://t.ly/LMqYW
import cv2 as cv
import numpy as np
from urllib.request import urlopen
import os
import datetime
import time
import sys

#change to your ESP32-CAM ip
url="http://192.168.1.123:9601/stream"
CAMERA_BUFFRER_SIZE=4096
stream=urlopen(url)
bts=b''
while True:
    bts+=stream.read(CAMERA_BUFFRER_SIZE)
    jpghead=bts.find(b'\xff\xd8')
    jpgend=bts.find(b'\xff\xd9')
    if jpghead>-1 and jpgend>-1:
        jpg=bts[jpghead:jpgend+2]
        bts=bts[jpgend+2:]
        img=cv.imdecode(np.frombuffer(jpg,dtype=np.uint8),cv.IMREAD_UNCHANGED)
        v=cv.flip(img,0)
        h=cv.flip(img,1)
        p=cv.flip(img,-1)        
        frame=p
        h,w=frame.shape[:2]
        img=cv.resize(frame,(800,600))
        cv.imshow("a",img)
    k=cv.waitKey(1)
    if k & 0xFF==ord('q'):
        break
cv.destroyAllWindows()


