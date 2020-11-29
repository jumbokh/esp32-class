### ESP32 Servo class
![ESP32](https://github.com/jumbokh/esp32-class/blob/master/images/ESP32s-pinout.png)
##
![SG9960](https://www.jsumo.com/mg996r-servo-motor-digital-1701-65-B.jpg)
## 
### 11/29 Lab
#### Description
* 1. 實驗步驟
      * 系統建置
      * 程式庫安裝
 ##
 #### code Link: [simple servo](https://github.com/jumbokh/esp32-class/blob/master/hs1129/src/01-SimpleServo/01-SimpleServo.ino)
 <pre>
 #include <Servo.h>

static const int servoPin = 13;

Servo servo1;

void setup() {
    Serial.begin(115200);
    servo1.attach(servoPin);
}

void loop() {
    for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
        servo1.write(posDegrees);
        Serial.println(posDegrees);
        delay(20);
    }

    for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
        servo1.write(posDegrees);
        Serial.println(posDegrees);
        delay(20);
    }
}
 </pre>
