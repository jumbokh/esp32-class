int redPin = 11;               //宣告紅色LED接腳 
int greenPin = 10;             //宣告綠色LED接腳
int bluePin = 9;               //宣告藍色LED接腳
void setup()
{
  pinMode(redPin, OUTPUT);     //設定紅色LED接腳
  pinMode(greenPin, OUTPUT);  //設定綠色LED接腳
  pinMode(bluePin, OUTPUT);   //設定藍色LED接腳
}
void loop()
{
analogWrite(redPin,0);          // 全暗
analogWrite(greenPin,0);
analogWrite(bluePin,0);
delay(1000);
analogWrite(redPin,255);       // 紅
analogWrite(greenPin,0);
analogWrite(bluePin,0);
delay(1000);
analogWrite(redPin,0);          // 綠
analogWrite(greenPin,255);
analogWrite(bluePin,0);
delay(1000);
analogWrite(redPin,0);          // 藍
analogWrite(greenPin,0);
analogWrite(bluePin,255);
delay(1000);
analogWrite(redPin,255);          // 白
analogWrite(greenPin,255);
analogWrite(bluePin,255);
delay(1000);
}

