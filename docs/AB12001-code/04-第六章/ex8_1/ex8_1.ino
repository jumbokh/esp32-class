//定義變數 
int a=2;                          //seg_a接到D2
int b=3;                          //seg_b接到D3
int c=4;                          //seg_c接到D4
int d=5;                          //seg_d接到D5 
int e=6;                          //seg_e接到D6
int f=7;                          //seg_f接到D7
int g=8;                          //seg_g接到D8
int dp=9;                          //seg_dp接到D9 
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
void setup() {                     //
    pinMode(a, OUTPUT); 
    pinMode(b, OUTPUT); 
    pinMode(c, OUTPUT); 
    pinMode(d, OUTPUT); 
    pinMode(e, OUTPUT); 
    pinMode(f, OUTPUT); 
    pinMode(g, OUTPUT); 
    pinMode(dp, OUTPUT); 
    digitalWrite(dp, 0);            // 關閉小數點 
} 
void loop() {
  for (byte digit = 0; digit <10; ++digit) {
    delay(1000);
    CodeWrite(digit); 
  }
 // 暫停 2 秒鐘
 delay(2000);
}
// 在七段顯示器上顯示指定的一個數字 
void CodeWrite(byte digit) {
  byte pin = 2;
  for (byte seg = 0; seg < 7; ++seg) {
    digitalWrite(pin, seven_seg[digit][seg]);
    ++pin;
  }
}

