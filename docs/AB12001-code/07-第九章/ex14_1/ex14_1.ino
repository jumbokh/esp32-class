#include <IRremote.h>
int Recv_Pin = 2;
IRrecv irrecv(Recv_Pin);
decode_results results;
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();                   //啟動紅外遙控
  pinMode(13,HIGH);
}
void loop() {
  if (irrecv.decode(&results)) {
     if(results.value== 0xFF30CF)         //確認接收到按鍵1的編碼
     {
        digitalWrite(13,HIGH);           //點亮LED
        Serial.println("turn on LED");   //串口顯示開燈
     }
  else if(results.value== 0xFF18E7)       //確認接收到按鍵2的編碼
       {
          digitalWrite(13,LOW );                //熄滅LED
          Serial.println("turn off LED");    //串口顯示關燈
       }
       irrecv.resume(); // 接收下一個值
  }
}

