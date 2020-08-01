#include<LiquidCrystal.h>	     //LiquidCrystal.h程式庫
LiquidCrystal lcd(12,11,5,4,3,2);     //LiquidCrystal.h程式庫對應接腳宣告
void setup(){
  lcd.begin(16,2);		           //LCD為2行，每行16(列)個字
  lcd.print("hello,world!");	          //LCD顯示文字
}
void loop(){
  lcd.setCursor(0,1);	      //設定游標在第1列第2行位置開始顯示
  lcd.print(millis()/1000);	 //在LCD列印Arduino重開之後經過的秒數
}

