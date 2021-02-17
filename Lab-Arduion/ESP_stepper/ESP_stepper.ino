#define A 14 //A 相線圈接到 Arduino Pin 14
#define B 12 //B 相線圈接到 Arduino Pin 12
#define A_BAR 13 // A_BAR 相線圈接到 Arduino Pin 13
#define B_BAR 15 // B_BAR 相線圈接到 Arduino Pin 15
#define rr 50 //轉速設定
#include <Stepper.h> //引入 Stepper.h 檔

Stepper stepper(200, A, A_BAR, B, B_BAR);

void setup(){
stepper.setSpeed(rr); //將馬達的速度設定成 50 RPM
}

void loop(){
stepper.step(2048); //順時針 1 圈
delay(2000);
stepper.step(-2048); //逆時針 1 圈
delay(2000);
}
