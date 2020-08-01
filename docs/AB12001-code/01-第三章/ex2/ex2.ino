int ledPin1=10;                      //設定控制LED的數位IO腳
int ledPin2=11;                      //設定控制LED的數位IO腳
void setup()
{
   pinMode(ledPin1,OUTPUT);      //設定數位IO口的模式，OUTPUT為輸出
   pinMode(ledPin2,OUTPUT);      //設定數位IO口的模式，OUTPUT為輸出
}
void loop()
{
   digitalWrite(ledPin1,HIGH);    //設定PIN10腳為HIGH=5V
   digitalWrite(ledPin2,LOW);     //設定PIN11腳為LOW=0V
   delay(1000);                    //設定延時時間，1000=1秒
   digitalWrite(ledPin1,LOW);     //設定PIN10腳為LOW=0V
   digitalWrite(ledPin2,HIGH);     //設定PIN11腳為HIGH=5V
   delay(1000);                    //設定延時時間，1000=1秒
}

