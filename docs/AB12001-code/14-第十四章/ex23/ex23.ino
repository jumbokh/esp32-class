#include <Servo.h>
Servo myservo;			//創建一個伺服馬達控制物件
int potpin=A0;			//A0用於儲存電位器讀出的模擬值
int val;			//該變數用於儲存伺服馬達角度位置
void setup()
{
myservo.attach(9);		//該伺服馬達由arduino第九腳控制
}
void loop()
{
val = analogRead(potpin);	//讀取可變電阻電位的模擬值(範圍在0-1023)
val = map(val,0,1023,0,180);	//將可變電阻電位值等比例成0~180
myservo.write(val); 			//指定伺服馬達轉向的角度
delay(15);					//等待15ms讓伺服馬達到達指定位置
}

