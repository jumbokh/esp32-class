// https://docs.google.com/document/d/1RYkLulmgV3cBIFqAiGqYBP6JTnoaNCQLFXJLoAC6yUE/edit
#include <BluetoothSerial.h>
BluetoothSerial BT;

void setup()
{
  Serial.begin(9600);
  BT.begin("jumbo-ESP32BT");//<<記得改名
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
