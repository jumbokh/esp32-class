#include <Servo.h> 
Servo myservo; 
void setup()  
{  
  Serial.begin(9600); 
  myservo.attach(9); 
}  
void loop()  
{  
  int d; 
  if(Serial.available()){ 
    d = Serial.parseInt(); 
    Serial.println(d); 
    if(0 <= d && d <= 180){ 
      myservo.write(d); 
    } 
  } 
} 

