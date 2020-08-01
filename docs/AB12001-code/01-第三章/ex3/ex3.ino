int led=9;                       //設定LED的數位IO腳為9
int brightness = 0;                //設定LED初始亮度0
int fadeAmount = 5;              //設定LED每次增量的幅度為5
void setup()
{
   pinMode(led,OUTPUT);                //宣告第9腳為OUTPUT(輸出)
}
void loop()
{
  analogWrite(led, brightness);             //LED做PWM輸出
  brightness = brightness + fadeAmount;   //每次迴圈增亮(變暗)一次
//假如亮度brightness=0或255，增量值fadeAmount變為負值
   if (brightness == 0 || brightness == 255) {
 fadeAmount = -fadeAmount ; 
   }  
  delay(30);                               //設定延時時間0.03秒
}

