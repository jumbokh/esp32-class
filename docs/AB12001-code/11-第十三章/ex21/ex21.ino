#define IN1 10       // 宣告馬達控制信號輸入端1
#define IN2 11       // 宣告馬達控制信號輸入端2
void setup() {
   pinMode(IN1, OUTPUT);     // 設定馬達控制腳1為輸出
   pinMode(IN2, OUTPUT);     // 設定馬達控制腳2為輸出
}
void loop() {
   digitalWrite(IN1,HIGH);     // 風扇正轉( 送風)
   digitalWrite(IN2,LOW);
   delay(5000);
   digitalWrite(IN1,HIGH);     // 風扇煞車
   digitalWrite(IN2,HIGH);
   delay(3000);
   digitalWrite(IN1,LOW);     // 風扇反轉( 吸風)
   digitalWrite(IN2,HIGH);
   delay(5000);
   digitalWrite(IN1,LOW);     // 風扇停止
   digitalWrite(IN2,LOW);
   delay(3000);
}

