#include <Servo.h>

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = 34;  // Analog input pin that the potentiometer is attached to
const int servoPin = 13;
// the number of the LED pin
const int ledPin = 19;  // 6 corresponds to GPIO6

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
Servo servo1;
int sensorValue = 0;        // value read from the pot
int servoPosition = 0;        // value output to the PWM (analog out)

void setup() {
  //宣告ledChannel特性
  ledcSetup(ledChannel, freq, resolution);
  
  //將上述ledChannel附加到ledPin腳位上
  ledcAttachPin(ledPin, ledChannel);
  servo1.attach(servoPin);
  // initialize serial communications at 9600 bps:
  Serial.begin(115200);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  servoPosition = map(sensorValue, 0, 4095, 0, 180);

  // changing the LED brightness with PWM
    ledcWrite(ledChannel, servoPosition);
    servo1.write(servoPosition);
  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(servoPosition);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2);
}
