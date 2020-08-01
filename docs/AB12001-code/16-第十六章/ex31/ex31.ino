#include <Ultrasonic.h>
#define Trip  3
#define Echo  2
Ultrasonic ultrasonic(Trip, Echo);
int IN1=12; 
int IN2=13;
void setup()  {
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
}
void loop()  {
  int cmMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  if ( cmMsec < 5 ) {
    
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,HIGH); 
    delay(1000);   
  }
}


