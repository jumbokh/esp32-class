import numpy as np
import cv2
from urllib.request import urlopen
import os
import datetime
import time
import sys
cascPath = 'haar/haarcascade_frontalface_default.xml'
eyecascPath = 'haar/haarcascade_eye.xml'
faceCascade = cv2.CascadeClassifier(cascPath)
eyeCascade = cv2.CascadeClassifier(eyecascPath)
#從 ESP32-CAM網路攝影機讀取影像
url = 'http://192.168.43.154:9601/stream'
#url = 'http://192.168.43.154:81'
CAMERA_NAME='ESPCAM01'
CAMERA_BUFFER_SIZE = 4096
stream = urlopen(url)
bbb = b''
while True:
    bbb += stream.read(CAMERA_BUFFER_SIZE)
    a = bbb.find(b'\xff\xd8')
    b = bbb.find(b'\xff\xd9')
 
    if a>-1 and b>-1:
       jpg = bbb[a:b+2]
       bbb = bbb[b+2:]
       img1 = cv2.imdecode(np.frombuffer(jpg, dtype=np.uint8), cv2.IMREAD_COLOR)
       img = cv2.flip(img1,1)
       gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
       faces = faceCascade.detectMultiScale(gray, 1.1, 8)
       # Draw a retangle around the faces
       for (x,y,w,h) in faces:
          cv2.retangle(img,(x,y),(x+w,y+h), (255,0,0),2)
          roi_gray = gray[y:y+h, x:x+w]
          roi_color = img[y:y+h, x:x+w]
          eyes = eyeCascade.detectMultiScale(roi_gray)
          for (ex,ey,ew,eh) in eyes:
              cv2.rectangle(roi_color, (ex,ey), (ex+ew,ey+eh),(0,255,0),2)
          # 顯示影像
          cv2.imshow(CAMERA_NAME, img)
    k = cv2.waitKey(1)
    # 若按下 q 鍵則離開迴圈
    if k & 0xFF == ord('q'):
       break
    elif k%256 == 32:
       #若按下space鍵,拍照
       path = './capture' #照片儲存的資料夾路徑
       date = datetime.datetime.now().strftime("%m_%d_%Y_%H_%M_%S")
       img_name = "opencv_frame_{}.png".format(date)  #照片命名
       cv2.imwrite(os.path.join(path, img_name), img) # 儲存照片
       print("{} writeten!".format(img_name))
# 關閉所有 opencv 視窗
cv2.destroyAllWindows()
         
       
