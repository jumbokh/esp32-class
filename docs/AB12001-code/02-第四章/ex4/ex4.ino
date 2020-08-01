int  buttonPin = 2;       //按鈕輸入接腳設定為2
int  ledPin = 13;         // LED燈接腳設定為13
int  buttonStatus;        //讀取按鈕狀態的變數
//按鈕及LED接腳輸出/輸入模式的設定
void setup() {            
    pinMode(ledPin, OUTPUT);         //將LED接腳設為輸出模式
    pinMode(buttonPin, INPUT);        //將按鈕接腳設為輸入模式
}
//迴圈程式
void loop() {                         
    buttonStatus = digitalRead(buttonPin);   //讀取按鈕開關狀態值
  //檢查按鈕是否按下
    if ( buttonStatus == LOW)        //假如成立，按鈕狀態為HIGH
    {                                       
        digitalWrite(ledPin,LOW);    //LED燈亮
    }
    else                             //否則，按鈕狀態為LOW
    {
        digitalWrite(ledPin,HIGH);          //LED燈暗
    }
}

