void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(13,INPUT);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(13) == 1) {
    Serial.println("Coming");
  }
  else {
    Serial.println("None");
  }
  delay(1000);
}
