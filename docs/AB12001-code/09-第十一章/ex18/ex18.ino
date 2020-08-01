#include "EEPROM.h"
int value;
int ii=0;
void setup() {
  Serial.begin(9600);
// 在EEPROM的第1到100位置上寫入數值1到100
  for( ii = 0;ii < 100;ii++)
       EEPROM.write(ii,ii);
}
void loop() {
  for(int i=0;i<100;i++){
    value = EEPROM.read(i);   //讀取EEPROM內位置1到100資料
// 將 value 輸出到 Serial port
    Serial.print("EEPROM Address =");// 會印出EEPROM Address =
    Serial.print(i,DEC);// 會印出內部記憶體位址
    Serial.print("   value=");// 會印出value=
    Serial.print(value,DEC);// 會印出記憶體資料 
    Serial.print("\n");
    delay(2000);
  }
}

