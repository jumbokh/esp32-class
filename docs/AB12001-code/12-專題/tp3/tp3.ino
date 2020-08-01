#include <IRremote.h>
int Recv_Pin = 13;
int IN1=10;
int IN2=11;
byte seg_Pin[]={3,4,5,6,7,8,9};
byte seg_Data[5][7]={{0,1,1,1,1,1,1},{0,0,0,0,1,1,0},{1,0,1,1,0,1,1},{1,0,0,1,1,1,1},{0,0,0,0,0,0,0}}; 
int mode = -1;
int mode_on = -1;
int ii;
IRrecv irrecv(Recv_Pin);
decode_results results;
void setup()
{
  pinMode(IN1, OUTPUT); 		// 初始化馬達控制腳為輸出
  pinMode(IN2, OUTPUT);
  irrecv.enableIRIn();                   //啟動紅外遙控
  for(ii=0;ii<7;ii++)
     pinMode(seg_Pin[ii],OUTPUT);
}
void loop() {
    if (irrecv.decode(&results)) {
     if(results.value== 0xFFE21D && mode_on!=1)         //確認接收到按鍵ON的編碼
     {
        CodeWrite (0);
        Serial.println("turn on");    //串口顯示關燈
        mode_on = 1;
        mode = -1;
     }
     else if(results.value== 0xFF30CF && mode!=1) { 
          if(mode_on==1)
           {
            CodeWrite (1);
            mode = 1;	
            analogWrite(IN1,255); 			// 風扇1速255
            digitalWrite(IN2,LOW);
          }
         }
     else if(results.value== 0xFF18E7 && mode!=2) { 
          if(mode_on==1)
           {
            CodeWrite (2);
            mode = 2;	
            analogWrite(IN1,210); 			// 風扇2速210
            digitalWrite(IN2,LOW);
          }
         }
     else if(results.value== 0xFF7A85 && mode!=3) { 
          if(mode_on==1)
           {
            CodeWrite (3);
            mode = 3;	
            analogWrite(IN1,160); 			// 風扇3速160
            digitalWrite(IN2,LOW);
          }
         }    
     else if(results.value== 0xFF629D && mode!=4) { 
          if(mode_on==1)
           {
            CodeWrite (4);
            mode = 4;	
            analogWrite(IN1,LOW); 			// 風扇off速
            digitalWrite(IN2,LOW);
            mode_on = -1;
          }
         }           
         irrecv.resume(); // 接收下一個值
  }
}
void CodeWrite(byte dat) {
for (ii=0; ii<7; ii++)
// 讀出 dat 指定位元，並顯示在對應七段顯示器的 pin 腳上
	digitalWrite(seg_Pin[ii], seg_Data[dat][ii]);
}

