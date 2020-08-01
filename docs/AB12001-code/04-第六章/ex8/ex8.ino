//定義變數 
int a=2;                          //seg_a接到D2
int b=3;                          //seg_b接到D3
int c=4;                          //seg_c接到D4
int d=5;                          //seg_d接到D5 
int e=6;                          //seg_e接到D6
int f=7;                          //seg_f接到D7
int g=8;                          //seg_g接到D8
int dp=9;                         //seg_dp接到D9 

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
//傳送0-9資料 
void loop() 
{ 
  digitalWrite(a, 1);                // 顯示 “0” 
  digitalWrite(b, 1); 
  digitalWrite(c, 1); 
  digitalWrite(d, 1); 
  digitalWrite(e, 1); 
  digitalWrite(f, 1); 
  digitalWrite(g,0); 
  delay(1000); 
  digitalWrite(a,0); // 顯示 “1” 
  digitalWrite(b, 1); 
  digitalWrite(c, 1); 
  digitalWrite(d, 0); 
  digitalWrite(e, 0); 
  digitalWrite(f, 0); 
  digitalWrite(g,0); 
  delay(1000);
  digitalWrite(a,1); // 顯示 “2” 
  digitalWrite(b, 1); 
  digitalWrite(c, 0); 
  digitalWrite(d, 1); 
  digitalWrite(e, 1); 
  digitalWrite(f, 0); 
  digitalWrite(g,1); 
  delay(1000);
  digitalWrite(a,1); // 顯示 “3” 
  digitalWrite(b, 1); 
  digitalWrite(c, 1); 
  digitalWrite(d, 1); 
  digitalWrite(e, 0); 
  digitalWrite(f, 0); 
  digitalWrite(g,1); 
  delay(1000);
  digitalWrite(a,0); // 顯示 “4” 
  digitalWrite(b, 1); 
  digitalWrite(c, 1); 
  digitalWrite(d, 0); 
  digitalWrite(e, 0); 
  digitalWrite(f, 1); 
  digitalWrite(g,1); 
  delay(1000);
  digitalWrite(a,1); // 顯示 “5” 
  digitalWrite(b, 0); 
  digitalWrite(c, 1); 
  digitalWrite(d, 1); 
  digitalWrite(e, 0); 
  digitalWrite(f, 1); 
  digitalWrite(g,1); 
  delay(1000);
  digitalWrite(a,1); // 顯示 “6” 
  digitalWrite(b, 0); 
  digitalWrite(c, 1); 
  digitalWrite(d, 1); 
  digitalWrite(e, 1); 
  digitalWrite(f, 1); 
  digitalWrite(g,1); 
  delay(1000);
  digitalWrite(a,1); // 顯示 “7” 
  digitalWrite(b, 1); 
  digitalWrite(c, 1); 
  digitalWrite(d, 0); 
  digitalWrite(e, 0); 
  digitalWrite(f, 0); 
  digitalWrite(g,0); 
  delay(1000);
  digitalWrite(a,1); // 顯示 “8” 
  digitalWrite(b, 1); 
  digitalWrite(c, 1); 
  digitalWrite(d, 1); 
  digitalWrite(e, 1); 
  digitalWrite(f, 1); 
  digitalWrite(g,1); 
  delay(1000);
  digitalWrite(a,1); // 顯示 “9” 
  digitalWrite(b, 1); 
  digitalWrite(c, 1); 
  digitalWrite(d, 1); 
  digitalWrite(e, 0); 
  digitalWrite(f, 1); 
  digitalWrite(g,1); 
  delay(1000);
}


