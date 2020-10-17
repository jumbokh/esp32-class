void setup() {
  Serial.begin(115200);
  pinMode(13, INPUT);//選告GPIO 13作為輸入（Mq2氣體感測）
}

void loop() {
  int GasValue;//宣告變數GasValue
  GasValue = analogRead(13); //讀取的GPIO 13讀取的數值放在GasValue
  Serial.println(GasValue); //GasValue顯示在序列視窗
  delay(100);
}
