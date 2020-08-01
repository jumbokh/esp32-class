//定義變數 
int a=2;                          //seg_a接到D2
int b=3;                          //seg_b接到D3
int c=4;                          //seg_c接到D4
int d=5;                          //seg_d接到D5 
int e=6;                          //seg_e接到D6
int f=7;                          //seg_f接到D7
int g=8;                          //seg_g接到D8
int dp=9;                          //seg_dp接到D9 
 int inPin = 11;                   //感測器輸入接腳
 int val = 0;                      //七段顯示器顯示數值 
int digit = 0;                     //七段顯示器顯示位數
//使用陣列指令將0-9編碼存在陣列內
byte  seven_seg[10][7] = { { 1,1,1,1,1,1,0 },  // = 0
{ 0,1,1,0,0,0,0 },  // = 1
{ 1,1,0,1,1,0,1 },  // = 2
{ 1,1,1,1,0,0,1 },  // = 3
{ 0,1,1,0,0,1,1 },  // = 4
{ 1,0,1,1,0,1,1 },  // = 5
{ 1,0,1,1,1,1,1 },  // = 6
{ 1,1,1,0,0,0,0 },  // = 7
{ 1,1,1,1,1,1,1 },  // = 8
{ 1,1,1,1,0,1,1 }   // = 9
                              };
void setup() {                     
pinMode(a, OUTPUT); 
pinMode(b, OUTPUT); 
pinMode(c, OUTPUT); 
pinMode(d, OUTPUT); 
pinMode(e, OUTPUT); 
pinMode(f, OUTPUT); 
pinMode(g, OUTPUT); 
pinMode(dp, OUTPUT); 
digitalWrite(dp, 0);            // 關閉小數點 
pinMode(inPin, INPUT); 
Serial.begin(9600); 
} 
void loop() {
     CodeWrite(digit);              //七段顯示器顯示數值
     val = digitalRead(inPin);        //讀取感測器數值
     if (val == HIGH) {              //假如偵測到物體
       delay(250);
       Serial.println(val);
       val = digitalRead(inPin);      //再讀取感測器數值
       if (val == LOW) {             //判斷物體是否離開了
         ++digit;                  //物體計數加1 
         if (digit > 9 ) digit = 0;     //假如物體計數超過9，計數器歸零
       }
      }
  }
//    delay(1000);

// 在七段顯示器上顯示指定的一個數字 
void CodeWrite(byte digit) {
  byte pin = 2;
  for (byte seg = 0; seg < 7; ++seg) {
    digitalWrite(pin, seven_seg[digit][seg]);
    ++pin;
  }
}

