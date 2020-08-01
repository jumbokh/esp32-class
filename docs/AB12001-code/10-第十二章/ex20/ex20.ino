/* 數位溫度計*/

const byte CS_Pin = 10; 		// 宣告TC77 的晶片選擇腳為D10
const byte Data_Pin = 11; 	// 宣告TC77 的資料腳為D11
const byte Clock_Pin = 13; 	// 宣告TC77 的CLK 為D13
int Value; 					// 建立符合TC77 資料格式的變數
float tempC;
//float  tempF;         // 宣告攝氏和華氏溫度變數
void setup() {
  pinMode (CS_Pin, OUTPUT); 	  //設定晶片選擇腳為輸出埠
  pinMode (Clock_Pin, OUTPUT);   //設定CLK腳為輸出埠
  pinMode (Data_Pin, INPUT);     //設定資料腳為輸入埠
  Serial.begin(9600);
}
void loop() {
  byte val1,val2;
  digitalWrite(CS_Pin,LOW); 	   // 指定CS=LOW，準備進行讀取
// 透過SPI 依序讀高8位元→val1，讀低8位元→val2
  val1=shiftIn(Data_Pin,Clock_Pin,MSBFIRST);
  val2=shiftIn(Data_Pin,Clock_Pin,MSBFIRST);
  digitalWrite(CS_Pin,HIGH);  // 讀取完成，讓CS=HIGH  
  Value = val1 * 256 + val2;   // 合成 16 位元的整數資料
  tempC = (Value>>3) * 0.0625; // 移除最低3無效位元後轉成攝氏溫度
 // tempF = 1.8 * tempC + 32.0;  // 轉換成華氏溫度
 
  Serial.println(tempC);            // 顯示取得的攝氏溫度
}

