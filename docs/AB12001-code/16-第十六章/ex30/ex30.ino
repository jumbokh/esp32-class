#include <Ultrasonic.h>
#include<LiquidCrystal.h>	     //LiquidCrystal.h程式庫
LiquidCrystal lcd(12,11,10,9,8,7);     //LiquidCrystal.h程式庫對應接腳宣告
#define Trip  3
#define Echo  2
Ultrasonic ultrasonic(Trip, Echo);
void setup()  {
  lcd.begin(16,2);		           //LCD為2行，每行16(列)個字
  lcd.print("Elect Ruler");	          //LCD顯示"Elect Ruler"  
}
void loop()  {
  int cmMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  lcd.setCursor(0,1);	      //設定游標在第1列第2行位置開始顯示
  lcd.print("Distance :");	 //在LCD列印Distance :
  lcd.print(cmMsec);	 //在LCD列印測出來的數值
  lcd.print(" CM ");	 //在LCD列印”CM”
  delay(1000);
  }
