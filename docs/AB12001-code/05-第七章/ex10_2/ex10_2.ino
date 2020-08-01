int sp=8;
int speed = 500;		//延遲500us
void setup()
{
pinMode(sp,OUTPUT);
}
void loop()
{
digitalWrite(sp,HIGH);
delayMicroseconds(speed);
digitalWrite(sp,LOW);
delayMicroseconds(speed);
}

