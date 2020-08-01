int ledPin=13;                     //設定控制LED的數位IO腳
void setup()
{
   pinMode(ledPin,OUTPUT);     //設定ledPin的模式為OUTPUT為輸出
}
void loop()
{
   digitalWrite(ledPin,HIGH);     //將PIN13腳設為HIGH=5V左右
   delay(1000);                  //設定延時時間，1000=1秒
   digitalWrite(ledPin,LOW);     //設定將PIN13腳為LOW=0V
   delay(1000);                 //設定延時時間，1000=1秒
}

