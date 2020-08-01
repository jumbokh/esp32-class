#include <Servo.h>
Servo myservo; // 建立Servo物件，控制伺服馬達

void setup() 
{ 
myservo.attach(9, 500, 2050); // 修正脈衝寬度範圍
myservo.write(90);
delay(1000);
} 
void loop() 
{
myservo.write(0);
delay(1000);
  myservo.write(30);
delay(1000);
myservo.write(60);
delay(1000);
myservo.write(90);
delay(1000);
myservo.write(120);
delay(1000);
myservo.write(150);
delay(1000); 
myservo.write(180);
delay(1000);
}

