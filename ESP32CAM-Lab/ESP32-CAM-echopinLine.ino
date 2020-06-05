int trigPin = 15;                  //請將Trig接GPIO15
int echoPin = 14;               //Echo Pin 接GPIO14
void setup() {
  Serial.begin (115200);             // Serial Port begin
  pinMode(trigPin, OUTPUT);        //Define inputs and outputs 
  pinMode(echoPin, INPUT);
}
 
void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);     // 給 Trig 高電位，持續 10微秒
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long cm = pulseIn(echoPin, HIGH);   // 收到高電位時的時間
 
  cm = (cm/2) / 29.1;         // 將時間換算成距離 cm 或 inch  
  //Serial.print("Distance : ");   
  Serial.println(cm);
  //Serial.print("cm");  
  delay(250);
}
