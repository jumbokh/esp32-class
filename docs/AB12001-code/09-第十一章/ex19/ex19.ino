#include <Wire.h>
void setup() 
{
  Wire.begin();
  Serial.begin(9600);
}
void loop() 
{
  byte men_data;
  // 設定HT24LC32 EEPROM address to 0
  Wire.beginTransmission(80);
  Wire.write(0);  			// 低位元組位址
  Wire.write(0);  			// 高位元組位址
  Wire.endTransmission();
  // 從位址0讀1 位元組
  Wire.requestFrom(80, 1);  	
  while(Wire.available()) {
  	men_data = Wire.read();
  }
  Serial.print("men_data = ");
  Serial.println(men_data, DEC);
  // men_data加1
  men_data++;
  // 將men_data值寫到HT24LC32 EEPROM 的位址0位置
  Wire.beginTransmission(80);
  Wire.write(0);    			//低位元組位址
  Wire.write(0);    			//高位元組位址
  Wire.write(men_data); 		// 將men_data資料寫到記憶體位址0內
  Wire.endTransmission();
  delay(1000);
}

