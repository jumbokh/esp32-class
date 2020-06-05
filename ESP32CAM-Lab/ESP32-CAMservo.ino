//Servo Org->GPIO 2, Red->VIN, GND->GND
//SG90 Servo 1638=0 degree, 4751=90 degree,7864=180 degree
void setup() {
  Serial.begin(115200);
  Serial.println("Open door");
  ledcSetup(1, 50, 16); // channel 1, 50 Hz, 16-bit width
  ledcAttachPin(2, 1);   // GPIO 2 assigned to channel 1
  for (int i = 1638 ; i < 7864 ; i = i + 100)
  {
    ledcWrite(1, i);       // sweep servo 1
    Serial.println(i);
    delay(200);
  }
  ledcDetachPin(1);// unsign channel 1
  delay(5000);
  ledcSetup(1, 50, 16); 
  ledcAttachPin(2, 1);   // GPIO 2 assigned to channel 1
  //Serial.println("opendoor");
  ledcWrite(1, 4751);//to 90 degree
  delay(5000);
  //Serial.println("closedoor");
  ledcWrite(1, 1638);//to 0 degree

}

void loop() {
  // put your main code here, to run repeatedly:

}

