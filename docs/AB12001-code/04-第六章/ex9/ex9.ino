int digit1 = 9; 	//顯示器位置1
int digit2 = 10; 	//顯示器位置2
int digit3 = 11; 	//顯示器位置3
int digit4 = 12; 	//顯示器位置4
int segA = 2;   	//A段LED pin 2
int segB = 3; 	//B段LED pin 3
int segC = 4; 	//C段LED pin 4
int segD = 5; 	//D段LED pin 5
int segE = 6; 	//E段LED pin 6
int segF = 7; 	//F段LED pin 7
int segG = 8; 	//G段LED pin 8
byte  seven_seg_digits[10][7] = 
{ { 1,1,1,1,1,1,0 },  // = 0
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
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);
}
void loop() {
  displayNumber(millis()/1000);   //輸出數字，約每秒加1
}
void displayNumber(int toDisplay) {
  #define DIGIT_ON  HIGH
  #define DIGIT_OFF  LOW
  //讓四個七段顯示器輪流ON/OFF
  for(int digit = 1 ; digit < 5  ; digit++) {
     switch(digit) {
     case 1:
       digitalWrite(digit1, DIGIT_ON);
       lightNumber(toDisplay % 10);     //取餘數
       toDisplay /= 10;                  //取商數
       break;
     case 2:
       digitalWrite(digit2, DIGIT_ON);
       lightNumber(toDisplay % 6);     //取餘數
       toDisplay /= 6;                  //取商數       
       break;
     case 3:
       digitalWrite(digit3, DIGIT_ON);
       lightNumber(toDisplay % 10);     //取餘數
       toDisplay /= 10;                  //取商數       
       break;
     case 4:
       digitalWrite(digit4, DIGIT_ON);
       lightNumber(toDisplay % 6);     //取餘數
       toDisplay /= 6;                  //取商數       
       break;
     }
     delayMicroseconds(6000);   //調整七段顯示器LED亮度1~6000
    lightNumber(10);                //關閉七段顯示器所有LED
    //關閉所有七段顯示器
    digitalWrite(digit1, DIGIT_OFF);
    digitalWrite(digit2, DIGIT_OFF);
    digitalWrite(digit3, DIGIT_OFF);
    digitalWrite(digit4, DIGIT_OFF);
  }
}
void lightNumber (byte numberToDisplay) {
  byte pin = 2;
  for (byte seg = 0; seg < 7; ++seg) {
    digitalWrite(pin, seven_seg_digits[numberToDisplay][seg]);
    ++pin;
  }
}

