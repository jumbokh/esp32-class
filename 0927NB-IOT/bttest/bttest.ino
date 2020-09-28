#include <BluetoothSerial.h>
BluetoothSerial BT;
void setup()
{
  Serial.begin(115200);
  BT.begin("Jumbo312");//請改名
}

void loop()
{
  BT.println("Hello World");
  delay(1000);
}
