## 以ESP32s在1602LCD上顯示溫濕度
### DHT11 溫濕度感測器
#### DHT 測試
#### 安裝程式庫
#### 要從DHT傳感器讀取數據，我們將使用Adafruit的DHT程式庫。要使用此程式庫，您還需要安裝Adafruit Unified Sensor程式庫。
* [Adafruit Unified Sensor Driver](https://github.com/adafruit/Adafruit_Sensor)
* [DHT sensor library](https://github.com/adafruit/DHT-sensor-library)
##
#### 以上程式庫安裝方法
* 下載後, 解壓縮
* 複製或移動到 文件->Arduino->libraries
* 重新啟動 Arduino IDE
##
### 測試程式
* [DHTTest](https://github.com/jumbokh/esp32-class/blob/master/arduino0920/DHTtester/DHTtester.ino)
<pre>
#define DHTPIN 5     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
</pre>
### 注意修改腳位及DHT Type
##
### 1602 LCD 測試
![ESP32+LCD](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2018/07/esp32_LCD_bb.png)
![連接](https://github.com/jumbokh/esp32-class/blob/master/images/ESP32-I2C-LCD-Interfacing.png)
#### 安裝程式庫
* [LCD Library](https://circuits4you.com/wp-content/uploads/2019/03/I2C-LCD-ESP8266-Library.zip)
##
### 測試LCD
* [I2C Scan]()
* [lcd I2C](https://github.com/jumbokh/esp32-class/blob/master/arduino0920/lcdi2c/lcdi2c.ino)
* [lcd Scroll](https://github.com/jumbokh/esp32-class/blob/master/arduino0920/lcdI2cScroll/lcdI2cScroll.ino)
##
### 整合 DHT 與 LCD
* [DHT LCD](https://github.com/jumbokh/esp32-class/blob/master/arduino0920/dhtlcdScroll/dhtlcdScroll.ino)
