const int relayPin=13;			//繼電器(Relay)
const int IN1=12;			    //IN1輸入
int relayState=0;					//繼電器狀態
void setup()	{
	Serial.begin(9600);			//開啟Serialport,通訊速率為9600bps
	pinMode(relayPin,OUTPUT);	//把relayPin設置成OUTPUT
}
void loop(){
  Serial.println("FAN is on");		//風扇啟動
  digitalWrite(relayPin,HIGH);
  digitalWrite(IN1,HIGH);
  delay(5000);
  Serial.println("FAN is off");		//風扇停止
  digitalWrite(relayPin,LOW);
  digitalWrite(IN1,LOW);
  delay(5000);
}

