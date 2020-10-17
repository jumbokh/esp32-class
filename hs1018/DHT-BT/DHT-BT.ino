
#include <BluetoothSerial.h>
BluetoothSerial BT;

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h"

#define DHTPIN 13     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(115200);
  Serial.println(F("DHTxx test!"));
  BT.begin("jumbo-ESP32BT");//<<記得改名
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) ) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));
  
   BT.print(F("Humidity: "));
   BT.print(h);
   BT.println("%");
   BT.print(F("Temperature: "));
   BT.print(t);
   BT.println("*C ");
}
