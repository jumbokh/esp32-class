//手機藍芽APP按鈕及語音控制家電
//filename:code_ESP32_NBIOT_BT_app_LED_FAN_jack_test_relay_ok1091008
//手機藍芽語音或按鍵控制家電 程式碼原始未編寫腳位與藍芽字元已編寫程式1090927
//filename:code_ESP32_NBIOT_bluetooth_app_LED_FAN_test_ok_1090927
//source:
//ESP32輔助版 藍芽語音辨識 智慧家電
//https://youyouyou.pixnet.net/blog/post/120569425-esp32%e8%bc%94%e5%8a%a9%e7%89%88-%e8%97%8d%e8%8a%bd%e8%aa%9e%e9%9f%b3%e8%be%a8%e8%ad%98-%e6%99%ba%e6%85%a7%e5%ae%b6%e9%9b%bb
//第十六篇 ESP32 藍芽BLE連線：即時通訊與語音指令
//https://youyouyou.pixnet.net/blog/post/120275962-%e7%ac%ac%e5%8d%81%e5%85%ad%e7%af%87-esp32-%e8%97%8d%e8%8a%bdble%e9%80%a3%e7%b7%9a%ef%bc%9a%e5%8d%b3%e6%99%82%e9%80%9a%e8%a8%8a

//手機APP關鍵字搜尋： arduino bluetooth control (broxcode)
//舊版手機APP：https://t.ly/3GPa
#include <BluetoothSerial.h>
BluetoothSerial BT;

void setup()
{
 // Serial.begin(115200);  //注意：NBIOT expanding board 之USB Power因共用1,3，導致Serial需要關閉 jack 1090927  
 //講師說設計瑕疵 暫用此腳位作為USB電燈與風扇腳位
 //故此手機藍芽控制此NBIOT板時需註解此行Serial.begin(115200)
  //BT.begin("ESP32");//<<記得改名
  BT.begin("jackESP32BLE1091008");
  //<<記得改名  手機要開藍芽/GPS定位???方可找到/並搜尋此名稱"jackESP32BLE1091008"
  //後連線arduinoAPP
  //範例程式：https://bit.ly/2EBzkEd
//注意：USB Power因共用1,3，導致Serial需要關閉
  pinMode(2,OUTPUT);//led pin2 on ESP32S board  @jack1091008
  pinMode(1,OUTPUT);//USB LED pin1 @jack1091008
  pinMode(3,OUTPUT);//USB FAN pin3 @jack1091008
  pinMode(22,OUTPUT);//relay1 pin22 @jack1091008 with 2relay module
  pinMode(23,OUTPUT);//relay2 pin23 @jack1091008 with 2relay module

 // pinMode(7,OUTPUT);//USB LED pin7 @jack1091008
 // pinMode(8,OUTPUT);//USB FAN pin8 @jack1091008
  
}

void loop()
{
  if(Serial.available())
  {
    String data=Serial.readString();
    BT.println(data);
  }
  if(BT.available()){Serial.println("");}
  while(BT.available())
  {
    char btdata=BT.read();
    Serial.print(btdata);
    if(btdata=='1'){digitalWrite(2,HIGH);} //led pin2 on ESP32S board  @jack1091008
    if(btdata=='2'){digitalWrite(2,LOW);} //led pin2 on ESP32S board  @jack1091008
    if(btdata=='3'){digitalWrite(1,HIGH);}  //USB LED pin1 @jack1091008
    if(btdata=='4'){digitalWrite(1,LOW);}   //USB LED pin1 @jack1091008
    if(btdata=='5'){digitalWrite(3,HIGH);}  //USB LED pin1 @jack1091008
    if(btdata=='6'){digitalWrite(3,LOW);}  //USB LED pin1 @jack1091008

    //if(btdata=='7'){digitalWrite(22,HIGH);}  //relay1 pin22 on  LED ON test ok @jack1091008  
    //if(btdata=='8'){digitalWrite(22,LOW);}  //relay1 pin22 off LED OFF test ok @jack1091008
    //if(btdata=='9'){digitalWrite(23,HIGH);}  //relay2 pin23 on LED ON test ok @jack1091008
    //if(btdata=='0'){digitalWrite(23,LOW);}  //relay2 pin23  off LED ON test ok @jack1091008  note:btdata=='10' 無法作用 字體也非藍色與前面123456789不同
    
    if(btdata=='7'){digitalWrite(22,LOW);}  //relay1 pin22 on @jack1091008  
    if(btdata=='8'){digitalWrite(22,HIGH);}  //relay1 pin22 off @jack1091008
    if(btdata=='9'){digitalWrite(23,LOW);}  //relay2 pin23 on @jack1091008
    if(btdata=='0'){digitalWrite(23,HIGH);}  //relay2 pin23 off @jack1091008  note:btdata=='10' 無法作用 字體也非藍色與前面123456789不同
    
        
  }  
  delay(1);
}
