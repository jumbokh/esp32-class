int sp=8;
int speed=1;           //延遲1ms
void setup() {
pinMode(sp,OUTPUT);
}
void loop()
{
digitalWrite(sp,HIGH);
delay(speed);
digitalWrite(sp,LOW);
delay(speed);
}

