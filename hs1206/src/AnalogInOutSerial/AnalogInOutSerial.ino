/*
  Analog input, analog output, serial output

  Reads an analog input pin, maps the result to a range from 0 to 255 and uses
  the result to set the pulse width modulation (PWM) of an output pin.
  Also prints the results to the Serial Monitor.

  The circuit:
  - potentiometer connected to analog pin 0.
    Center pin of the potentiometer goes to the analog pin.
    side pins of the potentiometer go to +5V and ground
  - LED connected from digital pin 9 to ground

  created 29 Dec. 2008
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogInOutSerial
*/

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = 34;  // Analog input pin that the potentiometer is attached to

// the number of the LED pin
const int ledPin = 13;  // 6 corresponds to GPIO6

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

int sensorValue = 0;        // value read from the pot
int dutyCycle = 0;        // value output to the PWM (analog out)

void setup() {
  //宣告ledChannel特性
  ledcSetup(ledChannel, freq, resolution);
  
  //將上述ledChannel附加到ledPin腳位上
  ledcAttachPin(ledPin, ledChannel);
  
  // initialize serial communications at 9600 bps:
  Serial.begin(115200);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  dutyCycle = map(sensorValue, 0, 4095, 0, 255);

  // changing the LED brightness with PWM
    ledcWrite(ledChannel, dutyCycle);

  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(dutyCycle);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2);
}
