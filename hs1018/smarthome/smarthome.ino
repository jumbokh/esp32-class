#include <BluetoothSerial.h>
BluetoothSerial SerialBT;//宣告藍芽物件=SerialBT

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//序列視窗
  SerialBT.begin("jumbo-ESP32BT");//<<藍芽廣播名稱，請自己記得
  pinMode(13,OUTPUT);//LED 1
  pinMode(18,OUTPUT);//LED 2
  pinMode(19,OUTPUT);//LED 3
}

void loop() {
  
  if(SerialBT.available()){
    Serial.println("");
  }
  while(SerialBT.available())
  {
    char btdata=SerialBT.read();
    Serial.print(btdata);//查看藍芽輸入的值
    if (btdata=='1'){digitalWrite(13,HIGH);}//LED1 ON
    if (btdata=='2'){digitalWrite(13,LOW);}//LED1 OFF
    if (btdata=='3'){digitalWrite(18,HIGH);}//LED2 ON
    if (btdata=='4'){digitalWrite(18,LOW);}//LED2 OFF 
    if (btdata=='5'){digitalWrite(19,HIGH);}//LED3 ON
    if (btdata=='6'){digitalWrite(19,LOW);}//LED3 OFF
  }  
  delay(100);
}
