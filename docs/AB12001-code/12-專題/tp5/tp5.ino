int IN1=10;
int IN2=11;
byte seg_Pin[]={9, 8, 7,6,5,4,3 };    //a,b,c,d,e,f,g
byte seg_Data[3][7] = { { 0,0,1,1,1,1,1 },{ 1,0,1,1,0,1,1 },  // b,S
                     { 1,0,0,0,1,1,1 }};    //F,""
const byte CS_Pin = A5; 		// 宣告TC77 的晶片選擇腳為D10
const byte Data_Pin = A3; 	// 宣告TC77 的資料腳為D11
const byte Clock_Pin = 2; 	// 宣告TC77 的CLK 為D13
int temp; 					// 建立符合TC77 資料格式的變數
float tempC;         			// 宣告攝氏溫度變數
int mode = -1;
int ii;
void setup()
{
  Serial.begin(9600);
  pinMode(IN1, OUTPUT); 		// 初始化馬達控制腳為輸出
  pinMode(IN2, OUTPUT);
  pinMode (CS_Pin, OUTPUT); 	  //設定晶片選擇腳為輸出埠
  pinMode (Clock_Pin, OUTPUT);   //設定CLK腳為輸出埠
  pinMode (Data_Pin, INPUT);     //設定資料腳為輸入埠
  for(ii=0;ii<7;ii++)
     pinMode(seg_Pin[ii],OUTPUT);
}
void loop() {
	byte val1,val2;
	digitalWrite(CS_Pin,LOW); 	   // 指定CS=LOW，準備進行讀取
// 透過SPI 依序讀高8位元→val1，讀低8位元→val2
	val1=shiftIn(Data_Pin,Clock_Pin,MSBFIRST);
	val2=shiftIn(Data_Pin,Clock_Pin,MSBFIRST);
	digitalWrite(CS_Pin,HIGH);//讀取完成，讓CS=HIGH
	temp = val1 * 256 + val2;//合成16位元的整數資料
	tempC = ( temp >> 3 ) * 0.0625;//移除最低3無效位元後轉成攝氏溫度
	Serial.print("Temp= ");
	Serial.println(tempC);
	if(tempC >= 30){
		digitalWrite(IN1,HIGH);			//風扇排風
		digitalWrite(IN2,LOW);
		CodeWrite(2);
		mode=1;
		}
	else if ( tempC <= 22)
	{
			if (mode==1){//風扇正在排風
				digitalWrite(IN1,LOW);			//風扇停止3秒鐘
				digitalWrite(IN2,LOW);
				CodeWrite(1);
				delay(3000);
			}
			CodeWrite(0);
			digitalWrite(IN1,LOW);			//風扇抽風
			digitalWrite(IN2,HIGH);
			mode=2;
	}
	else{
		CodeWrite(1);
		digitalWrite(IN1,LOW);			//風扇抽風
		digitalWrite(IN2,LOW);
		mode=-1;
	}
}
void CodeWrite(byte dat) {
for (ii=0; ii<7; ii++)
// 讀出 dat 指定位元，並顯示在對應七段顯示器的 pin 腳上
	digitalWrite(seg_Pin[ii], seg_Data[dat][ii]);
}

