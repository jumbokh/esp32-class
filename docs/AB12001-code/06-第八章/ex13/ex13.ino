#include<LiquidCrystal.h>	  //LiquidCrystal.h程式庫
LiquidCrystal lcd(12,11,5,4,3,2);  //LiquidCrystal.h程式庫對應接腳宣告
void setup()
{
lcd.begin(16, 2);               //LCD為2行，每行16(列)個字
lcd.clear();                    //清除螢幕
}
void loop()
{
lcd.clear();                     //清除螢幕
lcd.setCursor(3,0);             //文字顯示位置
lcd.print("Welcome to");        //LCD顯示文字
delay(1000);                   //文字顯示停留時間
lcd.setCursor(1,1);              //文字顯示位置
lcd.print("Arduino World!");   //LCD顯示文字
delay(3000);                   //文字顯示停留時間
lcd.clear();                    //清除螢幕
lcd.setCursor(5,0);             //文字顯示位置
lcd.print("We are ");           //LCD顯示文字
delay(1000);                   //文字顯示停留時間
lcd.setCursor(1,1);            //文字顯示位置
lcd.print("Arduino family");    //LCD顯示文字
delay(3000);                  //文字顯示停留時間
lcd.clear();                    //清除螢幕
lcd.setCursor(1,0);             //文字顯示位置
lcd.print("Arduino UNO R3 ");  //LCD顯示文字
delay(1000);                   //文字顯示停留時間
lcd.setCursor(4,1);             //文字顯示位置
lcd.print("Leonardo ");         //LCD顯示文字
delay(3000);                   //文字顯示停留時間
lcd.noDisplay();                //關閉LCD
delay(1000);                   //文字顯示停留時間
lcd.display();                   //開啟LCD
delay(1000);                   //延遲時間
}

