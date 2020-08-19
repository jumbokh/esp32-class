void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  pinMode(13, INPUT);//選告GPIO 13作為輸入（光敏電阻）
}

void loop() {
  int LightValue;//宣告變數LightValue
  LightValue = analogRead(13); //讀取的GPIO 13讀取的數值放在LightValue
  Serial.println(LightValue); //LightValue顯示在序列視窗
  if(LightValue>2000)
    digitalWrite(2,HIGH);
  else
    digitalWrite(2,LOW);
  delay(100);
}