### ESP32 實作研習
### ![ESP32](https://github.com/jumbokh/esp32-class/blob/master/images/ESP32s-pinout.png)
##
### ESP32CAM
### Windows 環境下操作, 請參考尤老師部落格：
[ESP32-CAM (arduino)影像伺服器及臉部辨識教學原始檔Video Stream Server](https://youyouyou.pixnet.net/blog/post/119383183)
### 或是
[ESP32-CAM Video Streaming and Face Recognition with Arduino IDE](https://randomnerdtutorials.com/esp32-cam-video-streaming-face-recognition-arduino-ide/)
### ![ESP32CAM--腳位](https://github.com/jumbokh/esp32-class/blob/master/images/ESP32CAM-pinout.jpeg)
### [入侵偵測](https://forum.amebaiot.com/t/iot-intruder-detection-system/341?fbclid=IwAR3QQSdKcStzmVRzlPOZx8jWH_k5N26iTe3pk4rKbg3vyFFx6XRusGpKGwk)
### 還有
[ESP32-CAM - A.I. Thinker](https://github.com/v12345vtm/esp32-cam-ai-thinker)
### [ESP32-CAM AI-Thinker Pinout Guide: GPIOs Usage Explained](https://randomnerdtutorials.com/esp32-cam-ai-thinker-pinout/)
### [AIoT之Python+ Arduino ESP32-CAM做人臉辨識](https://kobayasitenmei.pixnet.net/blog/post/227576372-aiot%e4%b9%8bpython%e7%a8%8b%e5%bc%8f%e7%a2%bc%2b-arduino-esp32-cam%e5%81%9a%e4%ba%ba%e8%87%89%e8%be%a8%e8%ad%98?pixfrom=related) {[src](https://github.com/jumbokh/esp32-class/blob/master/ESP32CAM-Lab/face_detect_esa32-cam01.py)}
### [haarcascades](https://github.com/opencv/opencv/tree/master/data/haarcascades)
### [ESP32-CAM Post Images to Local or Cloud Server using PHP (Photo Manager)](https://randomnerdtutorials.com/esp32-cam-post-image-photo-server/)
##
### 連線腳位
### ![ESP32CAM 串電腦](https://github.com/jumbokh/esp32-class/blob/master/images/ESP32cam-serial.jpeg)
### ![PL2303TA 下載線 USB轉TTL RS232模塊 ](https://github.com/jumbokh/esp32-class/blob/master/images/ESP32-CAM-cnt.png)
#### [Video Streaming Server on ESP32-CAM](https://medium.com/@chauhannaman98/video-streaming-server-on-esp32-cam-84e2ff788937)
##
### Lab
* 1. 測試Led補光 [src](https://github.com/jumbokh/esp32-class/blob/master/ESP32CAM-Lab/ESP32-CAM-Flash.ino)
* 2. 內建WebServer範例 [目錄](https://github.com/jumbokh/esp32-class/tree/master/ESP32CAM-Lab/CameraWebServer)
* 3. 修改過 WebServer ,SD卡寫入 [修改主程式](https://github.com/jumbokh/esp32-class/tree/master/ESP32CAM-Lab/ESP32-CAM_webcap)
* 4. 拍照存SD卡 [src](https://github.com/jumbokh/esp32-class/blob/master/ESP32CAM-Lab/ESP32-CAM-irdaSD.ino)
* 5. 超音波測試程式 [src](https://github.com/jumbokh/esp32-class/blob/master/ESP32CAM-Lab/ESP32-CAM-echopin.ino)
* 6. 超音波+Line通知範例程式 [src](https://github.com/jumbokh/esp32-class/blob/master/ESP32CAM-Lab/ESP32-CAM-echopinLine.ino)
* 7. [Telegram: ESP32 Motion Detection with Notifications (Arduino IDE)](https://randomnerdtutorials.com/telegram-esp32-motion-detection-arduino/)
    * ![HC-SR501](https://github.com/jumbokh/esp32-class/blob/master/images/HC-SR501.jpg)
### Python
#### [建制參考](https://medium.com/python4u/%E7%94%A8conda%E5%BB%BA%E7%AB%8B%E5%8F%8A%E7%AE%A1%E7%90%86python%E8%99%9B%E6%93%AC%E7%92%B0%E5%A2%83-b61fd2a76566)
* 1. [HelloWorld.py](https://github.com/jumbokh/esp32-class/blob/master/ESP32CAM-Lab/HelloWorld.py)
* 2. [Python使用WebCAM拍照 ](https://github.com/jumbokh/esp32-class/blob/master/ESP32CAM-Lab/ESP32-CAM-cap.py)
* 3. [Python開啟ESP32CAM ](https://github.com/jumbokh/esp32-class/blob/master/ESP32CAM-Lab/ESP32-CAM.py)
* 4. [opencv 測試](https://github.com/jumbokh/esp32-class/blob/master/ESP32CAM-Lab/cvtest.py)
* 5. [Arduino: ESP32CAM紅外線SD卡](https://github.com/jumbokh/esp32-class/blob/master/ESP32CAM-Lab/ESP32-CAM-irdaSD-org.ino)
* 6. [ESP32CAM+Yolo v3+Line](https://github.com/jumbokh/esp32-class/blob/master/ESP32CAM-Lab/ESP32-CAMdetLine.py)
* 7. [GETTING STARTED WITH ESP32 ESP-IDF (PART 2)](http://iot-bits.com/esp32/getting-started-with-esp32-esp-idf-part-2/)
* 8. [ESP32-CAM Post Images to Local or Cloud Server using PHP (Photo Manager)](https://randomnerdtutorials.com/esp32-cam-post-image-photo-server/)
##ESP32-CAM Post Images to Local or Cloud Server using PHP (Photo Manager)
#### [40+ ESP32-CAM Projects, Tutorials and Guides with Arduino IDE](https://randomnerdtutorials.com/projects-esp32-cam/?fbclid=IwAR1a0nwQYBc8E9HtxgT1Zi0zD-2mgmBC1ZZo3bpc-URBOLfJjD_XlXc4fTE)
### AI 應用
* 7. [訓練自己的臉部辨識特徵](https://github.com/jumbokh/cv_face/tree/master/opencv/day3)
* 8. [開門](https://github.com/jumbokh/esp32-class/blob/master/ESP32CAM-Lab/ESP32-CAMdoor.py)
* 9. [Darknet using Colab](https://nbviewer.jupyter.org/github/jumbokh/esp32-class/blob/master/ESP32CAM-Lab/Yolov3_Darknet_on_Colab.ipynb)
* 10. [Arduino: 伺服馬達控制](https://github.com/jumbokh/esp32-class/blob/master/ESP32CAM-Lab/ESP32-CAMservo.ino)
* 11. [Arduino: Web伺服馬達控制](https://github.com/jumbokh/esp32-class/blob/master/ESP32CAM-Lab/ESP32-CAMservo-1.ino)
