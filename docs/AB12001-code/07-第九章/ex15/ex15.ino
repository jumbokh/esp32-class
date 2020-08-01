int ledPin=13;                       //LED接在的13接腳
int inPin=7;                         //TCRT5000輸入接腳
int val=0;                           
void setup(){
  pinMode(ledPin,OUTPUT);        
  pinMode(inPin,INPUT);           
}
void loop(){
  val=digitalRead(inPin);            //讀取TCRT5000感測器訊號
  if(val==HIGH){                   //假如感測到物體
  digitalWrite(ledPin,HIGH);         //LED亮
  } else {
     digitalWrite(ledPin,LOW);      //LED暗
   }
}

