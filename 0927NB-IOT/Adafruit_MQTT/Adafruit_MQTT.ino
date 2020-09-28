#include <WiFi.h>
#include "Adafruit_MQTT.h" //安裝Adafruit MQTT
#include "Adafruit_MQTT_Client.h"
/**** WiFi Access Point ***************/
#define WLAN_SSID       "jumboap"
#define WLAN_PASS       "0953313123"
// ******** Adafruit.io Setup ******************/
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                 
#define AIO_USERNAME    "jumbokh"
#define AIO_KEY         "aio_UUJU07swPCCzW0Pg7Ak0OkZ3vsB0"
// Create an ESP32 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// Setup the MQTT client class by passing in the WiFi client 
// and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
/****************************** Feeds ***************************************/
//Publish.
// Notice MQTT paths for AIO follow the form: username /feeds/ feedname;
//Adafruit_MQTT_Publish touch_sensor = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/touch_sensor");
//Subscribe
// 訂閱 'CON' for subscribing to changes.
Adafruit_MQTT_Subscribe LED_Control = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/CON");
/*************************** Sketch Code ************************************/
void MQTT_connect(); 
uint8_t ledPin = 2;
uint16_t potAdcValue = 0;
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);
  pinMode(ledPin,OUTPUT);
   
  Serial.println(F("Adafruit MQTT demo"));
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());
 
  // Setup MQTT subscription for ledBrightness feed.
  mqtt.subscribe(&LED_Control);
   
 
}
 
void loop() {
  // put your main code here, to run repeatedly:
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();
 
  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here
 
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(1000))) {
    if (subscription == &LED_Control) {
      Serial.print(F("Got LED State: "));
      Serial.println((char *)LED_Control.lastread);
      //ledBrightValue = atoi((char *)LED_Control.lastread);
      //Serial.println(ledBrightValue);
      //analogWrite(ledPin, ledBrightValue);
      if (!strcmp((char*) LED_Control.lastread, "ON"))
      {
        digitalWrite(ledPin, HIGH);
      }
      else {
        digitalWrite(ledPin, LOW); 
      }
     }
  }

   
}
 
// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;
 
  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }
 
  Serial.print("Connecting to MQTT... ");
 
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(3000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
