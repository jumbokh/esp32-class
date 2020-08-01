int sp=8;
void setup(){
   pinMode(sp,OUTPUT);
}
void loop()
{
tone(sp,500);
delay(500);
tone(sp,1000);
delay(500);
}

