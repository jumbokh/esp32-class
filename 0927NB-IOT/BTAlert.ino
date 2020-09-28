#include <BluetoothSerial.h>
BluetoothSerial BT;
//本例請將
void setup() {
  Serial.begin(115200);
  pinMode(39,INPUT);
  BT.begin("Eric1030");//請改名
}

void loop() {
  int air = analogRead(39);//氣體感測
  BT.print("Air=");
  BT.println(air);
  //休息1.5秒
  delay(1000);
  
}

