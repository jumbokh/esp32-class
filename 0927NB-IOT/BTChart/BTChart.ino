#include <BluetoothSerial.h>
BluetoothSerial BT;

void setup()
{
  Serial.begin(115200);
  BT.begin("Jumbo312");//<<記得改名
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
  }  
  delay(10);
}
