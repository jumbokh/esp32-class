### 雲端服務應用範例
##
#### [講義](https://github.com/jumbokh/esp32-class/blob/master/Lab-Cloud/MQTT.pptx)
##
#### Lab 1 DHT11 測試
* 測試 DHT11 溫濕度感測器 [src](https://github.com/jumbokh/esp32-class/blob/master/Lab-Cloud/dhttest.py)
* ![DHT11接線](https://github.com/jumbokh/esp32-class/blob/master/images/dht11-esp32.jpg)
##
#### Lab 2 MQTT Broker
* 於手機下載安裝 [MQTT Broker app](https://play.google.com/store/apps/details?id=server.com.mqtt)
* 設定 Broker: gpssensor.ddns.net:1883
* 設定 subscribe/publish
    * topic_pub = b'/iotclass/T'
    * topic_pub1 = b'/iotclass/H'
    * topic_sub = b'/iotclass/lamp'
    * topic_sub1 = b'/iotclass/TH'
* mqtt client python: [src](https://github.com/jumbokh/esp32-class/blob/master/Lab-Cloud/Lab-MQTT-DHT.py)
    * [mqtt module](https://github.com/jumbokh/esp32-class/blob/master/Lab-Cloud/umqttsimple.py)
 ##
 #### Lab 3 中華電信智慧物聯網平台測試
 ＊＊ 參考 [Lab-walk中的設定](https://github.com/jumbokh/esp32-class/blob/master/Lab-walk/README.md)
 * [src](https://github.com/jumbokh/esp32-class/blob/master/Lab-Cloud/CHT-iotmqtt.py)
 ＊＊ 
