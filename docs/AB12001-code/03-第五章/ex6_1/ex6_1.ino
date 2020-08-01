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
  setColor(255, 0, 0);           // 紅
  delay(1000);
  setColor(0, 255, 0);           // 綠
  delay(1000);
  setColor(0, 0, 255);           // 藍
  delay(1000);
  setColor(255, 255, 0);        // 黃
  delay(1000);  
  setColor(255, 0,255);         // 紫
  delay(1000);
  setColor(0, 255, 255);        // 青
  delay(1000);
  setColor(255, 255, 255);      // 白
  delay(1000);  
}
//顏色調配副程式
void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}

