#include <BluetoothSerial.h>
BluetoothSerial BT;

void setup()
{
  //Serial.begin(115200);
  BT.begin("Jumbo312");//<<記得改名
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
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
    if(btdata=='1'){digitalWrite(2,HIGH);}
    if(btdata=='2'){digitalWrite(2,LOW);}
    if(btdata=='3'){digitalWrite(1,HIGH);} //靠外的USB
    if(btdata=='4'){digitalWrite(1,LOW);}
    if(btdata=='5'){digitalWrite(3,HIGH);}
    if(btdata=='6'){digitalWrite(3,LOW);}
  }  
  delay(10);
}
