#define trigPin 3
#define echoPin 2
void setup()
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
 }
void loop()
{
  int duration, distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*0.034/2) ;// 29.1; //konwersja na centrymetry
  Serial.print("Dystans = ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(500);
}
