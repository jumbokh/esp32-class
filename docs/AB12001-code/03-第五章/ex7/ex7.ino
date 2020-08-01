#define LEDR 11
#define LEDG 10
#define LEDB 9
void setup() {                
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
}
int red = 0;
int green = 0;
int blue = 0;
void loop() {
  red = random(0, 255);
  green = random(0, 255);
  blue = random(0, 255);
  analogWrite(LEDR, red);
  analogWrite(LEDG, green);
  analogWrite(LEDB, blue);
  delay(1000);
}

