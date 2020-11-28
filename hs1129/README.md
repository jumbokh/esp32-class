### ESP32 servo pwm
## 2020/11/29 ESP32 LAB
### 材料清單:
* ESP32S * 1
* Micro USB 通訊線 * 1
* 10k 旋轉可變電阻
* SG90 伺服馬達
* USB LED 燈
* USB 風扇
* 繼電器 模組 * 1
* Half+ 麵包板 * 1
* 杜邦線 少許
##
### Lab 1 旋轉可變電阻
* ![旋轉可變電阻](https://github.com/jumbokh/esp32-class/blob/master/images/potimeter.jpg)
* ![接腳](https://github.com/jumbokh/esp32-class/blob/master/images/potimeter_bb.jpg)
#### 讀取值： 0v ~ 3.3v 轉換： 0~4095
* [src](https://github.com/jumbokh/esp32-class/blob/master/hs1129/src/AnalogReadin.ino)
##
### Lab 2 PWM LED
* ![pwm led](https://github.com/jumbokh/esp32-class/blob/master/images/pwm-led_bb.jpg)
* [src](https://github.com/jumbokh/esp32-class/blob/master/hs1129/src/AnalogInOutSerial/AnalogInOutSerial.ino)
##
### Lab 3 Simple Servo -- 0~180 度旋轉
#### Library: [ESP32Servo](https://github.com/jumbokh/esp32-class/tree/master/hs1129/libraries/ESP32Servo)
* ![SG90接線圖](https://github.com/jumbokh/esp32-class/blob/master/images/SG90.jpg)
* ![servo](https://github.com/jumbokh/esp32-class/blob/master/images/servo.png)

