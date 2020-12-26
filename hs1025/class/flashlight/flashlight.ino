void setup() {
  // put your setup code here, to run once:
pinMode(4,OUTPUT);//pin4->flashlight
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(4,HIGH);
delay(500);
digitalWrite(4,LOW);
delay(5000);
}

