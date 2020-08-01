#define relayPin 13       //定義繼電器接腳為13
#define IN1 12          //定義IN1接腳為12
#define OnPin 2         //定義ON按鈕開關接腳為2
#define OffPin 3         //定義OFF按鈕開關接腳為3
int val = 0;             //變數val用來儲存按鈕狀態
int val1 = 0;            //變數val1用來儲存按鈕狀態
int state = 0;           //1表示ON按鍵按下，0表示OFF按下
void setup(){
  pinMode(relayPin, OUTPUT);     //設定繼電器接腳為輸出狀態
  pinMode(IN1, OUTPUT);        //設定IN1接腳為輸出狀態
  pinMode (OnPin,INPUT);        //設定按鈕ON接腳為輸入狀態
  pinMode (OffPin,INPUT);        //設定按鈕OFF接腳為輸入狀態
}
void loop(){
  val = digitalRead(OnPin);             //讀取ON按鈕狀態並儲存
  if((val == LOW)&&(state== 0)){ 		  //檢查按鈕的變化情況
    state =1;
	digitalWrite(relayPin,HIGH);
	digitalWrite(IN1,HIGH);
    delay(40);                       //延時抗按鈕彈跳
  }
  val1 = digitalRead(OffPin);           //讀取按鈕OFF狀態並儲存
  if((val1 == LOW)&&(state == 1)){ 	 //檢查按鈕的變化情況
    state =0;
	digitalWrite(relayPin,LOW);
	digitalWrite(IN1,LOW);
    delay(40);                      //延時抗按鈕彈跳
  }
}

