int ledPin=13;               
int inPin=7;                 
int val=0;                    
void setup(){
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);    
  pinMode(inPin,INPUT);        
}
void loop(){
  val=analogRead(0);
  Serial.println(val);
  analogWrite(ledPin,map(val,0,500,0,255));
}

