/*
* ESP32 Hello World
* ESP-WROOM-32
* Hardware: ESP32 Development Kit v1 (DOIT Board)
* Code Written by T.K.Hareendran
* Read the tutorial first, and then proceed!
*/
const int ledPin = 18; // User LED is connected to Pin 24
const int ledPin1 = 19; // User LED is connected to Pin 24
void setup() {
pinMode (ledPin, OUTPUT); //GPIO18 as Output
pinMode (ledPin1, OUTPUT); //GPIO19 as Output
}

void loop() {
digitalWrite (ledPin, HIGH);
digitalWrite (ledPin1, LOW);
delay(500);
digitalWrite (ledPin1, HIGH);
digitalWrite (ledPin, LOW);
delay(500);
}
