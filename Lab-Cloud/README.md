### 雲端服務應用範例
##
#### [講義](https://github.com/jumbokh/esp32-class/blob/master/Lab-Cloud/MQTT.pptx)
##
#### Lab 1 DHT11 測試
* 測試 DHT11 溫濕度感測器 [src](https://github.com/jumbokh/esp32-class/blob/master/Lab-Cloud/dhttest.py)
* ![DHT11接線](https://github.com/jumbokh/esp32-class/blob/master/images/dht11-esp32.jpg)
##
#### Lab 2 MQTT Broker
* 於手機下載安裝 
* APP 1 : [MQTT Broker app](https://play.google.com/store/apps/details?id=server.com.mqtt)
![Broker setup](https://github.com/jumbokh/esp32-class/blob/master/Lab-Cloud/13440101835269.jpg)
![subscribe](https://github.com/jumbokh/esp32-class/blob/master/Lab-Cloud/13440101807799.jpg)
![message](https://github.com/jumbokh/esp32-class/blob/master/Lab-Cloud/13440101784616.jpg)
* APP 2 : [MQTT Dash](https://play.google.com/store/apps/details?id=net.routix.mqttdash)
* 設定 Broker: gpssensor.ddns.net:1883
![mqtt client](https://github.com/jumbokh/esp32-class/blob/master/Lab-Cloud/conn-broker.jpg)

* 設定 subscribe/publish
    * topic_pub = b'/iotclass/T'
    * topic_pub1 = b'/iotclass/H'
    * topic_sub = b'/iotclass/lamp'
    * topic_sub1 = b'/iotclass/TH'
![subscribe H](https://github.com/jumbokh/esp32-class/blob/master/Lab-Cloud/Topic-H.jpg)
![message receive](https://github.com/jumbokh/esp32-class/blob/master/Lab-Cloud/Topic-receive.jpg)
![on the program side](https://github.com/jumbokh/esp32-class/blob/master/Lab-Cloud/mqttrun.png)
* mqtt client python: [src](https://github.com/jumbokh/esp32-class/blob/master/Lab-Cloud/Lab-MQTT-DHT.py)
    * [mqtt module](https://github.com/jumbokh/esp32-class/blob/master/Lab-Cloud/umqttsimple.py)
 ##
 #### Lab 3 中華電信智慧物聯網平台測試
 ＊＊ 參考 [Lab-walk中的設定](https://github.com/jumbokh/esp32-class/blob/master/Lab-walk/README.md)
 * [src](https://github.com/jumbokh/esp32-class/blob/master/Lab-Cloud/CHT-iotmqtt.py)
 ＊＊ 
