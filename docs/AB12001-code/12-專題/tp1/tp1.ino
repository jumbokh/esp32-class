/* 戶外活動溫度指示器*/
const byte CS_Pin = 4; 				// 指定TC77 的CS腳為D4
const byte SCK_Pin = 5; 				// 指定TC77 的SCK 為D5
const byte Data_Pin = 6; 				// 指定TC77 的SI/O腳為D6
const byte RGBled[3] = {9,10,11};		 // 宣告RGB LED 的腳位
//宣告紅色，紫色，黃色，綠色和藍色的 RGB 數值
const byte RGB[5][3] = { {255,0,0},{153,50,205},{255,255,0},{0,255,0},{0,0,255}};
int i ;								
int color ;							//紀錄現在溫度狀態
int Temp; 							// 建立存放TC77 資料的變數
float TempC;	 						// 宣告攝氏溫度變數

void setup() {
	pinMode (CS_Pin, OUTPUT); 			// 指定CS接腳為輸出埠
	pinMode (SCK_Pin, OUTPUT); 		// 指定SCK接腳為輸出埠
	pinMode (Data_Pin, INPUT); 			// 指定Data接腳為輸入埠
	for(i=0;i<3;i++)
	pinMode (RGBled[i], OUTPUT); 		// 指定RGB LED 接腳為輸出埠
	Serial.begin(9600);
}
void loop() {
	byte val1,val2;
	digitalWrite(CS_Pin,LOW); 			// 指定CS=LOW，準備進行讀取動作
	// 依序讀高8位元→ val1，讀低8位元→ val2
	val1=shiftIn(Data_Pin,SCK_Pin,MSBFIRST);
	val2=shiftIn(Data_Pin,SCK_Pin,MSBFIRST);
	// 讀取完成，讓CS=HIGH 變成非選擇狀態
	digitalWrite(CS_Pin,HIGH);
	Temp = val1 * 256 + val2; 		// 16 位元整數資料形態（最高位元為正負號）
	TempC = (Temp>>3) * 0.0625; 		// 移除最低3無效位元後轉成攝氏溫度
	if (TempC>=35) 					    //35度以上(紅色) 
		color=0;
	else if (TempC>=31) 					// 31~35度(紫色)
		color=1;
	else if (TempC>=28) 					// 28 ~ 31度(黃色)
		color=2;
	else if (TempC>=24) 					// 24 ~ 28度 (綠色)
		color=3;
	else 								// 24 度以下(藍色)
		color=4;
	Serial.print("TempC="); 					// 在串列埠上顯示溫度值
	Serial.print("\t"); 					// 顯示定位符號
	Serial.println(color); 					// 顯示顏色索引值
	for (i=0; i<3; i++) 					// 依序輸出指定顏色索引值的RGB 值
		analogWrite(RGBled[i],RGB[color][i]); 
		delay(1000);
}

