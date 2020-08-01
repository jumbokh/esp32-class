#include <IRremote.h>
int Recv_Pin = 13;
int IN1=10;
int IN2=11;
byte seg_Pin[]={9, 8, 7,6,5,4,3 };
byte  seg_Data[11][7] = { { 0,0,0,1,1,1,0 },{ 1,1,0,1,1,0,1 },  // L,2
{ 1,1,1,1,0,0,1 },{ 0,1,1,0,0,1,1 },  // 3 ,4                     
                  { 1,0,1,1,0,1,1 },{ 1,0,1,1,1,1,1 },  // 5,6
                  { 1,1,1,0,0,0,0 },{ 1,1,1,1,1,1,1 },  //7,8
                  { 1,1,1,0,0,1,1 },{ 0,1,1,0,1,1,1 },  // 9,H
                  { 0,0,0,0,0,0,0 } };
const byte CS_Pin = A5; 		// 宣告TC77 的晶片選擇腳為D10
const byte Data_Pin = A3; 	// 宣告TC77 的資料腳為D11
const byte Clock_Pin = 2; 	// 宣告TC77 的CLK 為D13
int temp; 					// 建立符合TC77 資料格式的變數
float tempC;         // 宣告攝氏和華氏溫度變數
int mode = -1;
int ii;
IRrecv irrecv(Recv_Pin);
decode_results results;
void setup()
{
  Serial.begin(9600);
  pinMode(IN1, OUTPUT); 		// 初始化馬達控制腳為輸出
  pinMode(IN2, OUTPUT);
  pinMode (CS_Pin, OUTPUT); 	  //設定晶片選擇腳為輸出埠
  pinMode (Clock_Pin, OUTPUT);   //設定CLK腳為輸出埠
  pinMode (Data_Pin, INPUT);     //設定資料腳為輸入埠
  irrecv.enableIRIn();                   //啟動紅外遙控
  for(ii=0;ii<7;ii++)
     pinMode(seg_Pin[ii],OUTPUT);
}

void loop() {
    if (irrecv.decode(&results)) {
     if(results.value== 0xFFE21D && mode!=1)    //確認接收到按鍵ON的編碼
         mode = 1;
     else if(results.value== 0xFF629D && mode!=-1)
         mode = -1;
     irrecv.resume(); // 接收下一個值
    } 
     if(mode == 1) 
     {
          byte val1,val2;
          digitalWrite(CS_Pin,LOW); 	   // 指定CS=LOW，準備進行讀取
          // 透過SPI 依序讀高8位元→val1，讀低8位元→val2
          val1=shiftIn(Data_Pin,Clock_Pin,MSBFIRST);
          val2=shiftIn(Data_Pin,Clock_Pin,MSBFIRST);
          digitalWrite(CS_Pin,HIGH);  // 讀取完成，讓CS=HIGH  
          temp = val1 * 256 + val2;   // 合成 16 位元的整數資料
          tempC = (temp>>3) * 0.0625; // 移除最低3無效位元後轉成攝氏溫度
          int Speed = 55+(tempC-15)*10;
          Serial.print("Temp=");
           Serial.println(tempC);           
          analogWrite(IN1,Speed); 
         CodeWrite ((tempC-15)/2);
          mode = 1;
     }
     else if(mode==-1)  
     {
            CodeWrite (10);
            analogWrite(IN1,LOW); 			// 風扇off速
            digitalWrite(IN2,LOW);
     }           
}
void CodeWrite(byte dat) {
for (ii=0; ii<7; ii++)
// 讀出 dat 指定位元，並顯示在對應七段顯示器的 pin 腳上
	digitalWrite(seg_Pin[ii], seg_Data[dat][ii]);
}

