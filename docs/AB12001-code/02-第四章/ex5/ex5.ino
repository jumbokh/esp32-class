int potPin = A3;          // 宣告可變電阻輸入接腳
int ledPin = 9;            // 宣告LED連接接腳
void setup() {
  Serial.begin(9600);    //設定SerialPort的傳輸速率
}
void loop() {
  int sensorValue = analogRead(potPin); //讀取可變電阻值
  Serial.println(sensorValue, DEC);       //將電阻值列印到 SerialPort
  sensorValue = sensorValue/4;         //將電阻值轉換成0-255範圍內
  analogWrite(ledPin, sensorValue);     //類比輸出LED亮度
  delay(150);
}  

