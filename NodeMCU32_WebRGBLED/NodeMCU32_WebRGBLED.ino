/* 
 *  This sketch run on ESP32 with Arduino core for ESP32,
 *  demonstrates how to set up a simple HTTP-like server.
 *  The server will set a GPIO pins depending on the request,
 *  to control the brightness of RGB LED connected to:
 *    23 : BLUE
 *    22 : GREEN
 *    21 : RED
 *    
 *    http://server_ip/rgb/rrggbb/
 *    where rr is the value set RED
 *    where gg is the value set GREEN
 *    where bb is the value set BLUE
 *    then terminate with '/'
 *  server_ip is the IP address of the ESP32, will be 
 *  printed to Serial when the module is connected.
*/
#include <WiFi.h>

const char* ssid = "informatics";
const char* password = "0953313123";
WiFiServer server(80);

#define MAX_LED_VALUE 99
// use first 3 channels of 16 channels (started from zero)
#define LEDC_CHANNEL_0_R  0
#define LEDC_CHANNEL_1_G  1
#define LEDC_CHANNEL_2_B  2

// use 13 bit precission for LEDC timer
#define LEDC_TIMER_13_BIT  13

// use 5000 Hz as a LEDC base frequency
#define LEDC_BASE_FREQ     5000

// LED PINs
#define LED_PIN_R   18
#define LED_PIN_G   19
#define LED_PIN_B   2

/*
Because Multiple libraries were found for "WiFi.h",
Arduino IDE will: 
 Used: ...\Arduino\hardware\espressif\esp32\libraries\WiFi
 Not used: C:\Program Files (x86)\Arduino\libraries\WiFi

And exit with error:
'min' was not declared in this scope

So I have to program my own min()
 */
uint32_t min(uint32_t num1, uint32_t num2){
  if(num1 < num2){
    return num1;
  }else{
    return num2;
  }
}

// Arduino like analogWrite
// value has to be between 0 and valueMax
void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = MAX_LED_VALUE) {
  // calculate duty
  uint32_t duty = (LEDC_BASE_FREQ / valueMax) * min(value, valueMax);

  // write duty to LEDC
  ledcWrite(channel, duty);
}

void setup() {
  Serial.begin(115200);
  delay(10);
  
  // Setup timer and attach timer to a led pins
  ledcSetup(LEDC_CHANNEL_0_R, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
  ledcAttachPin(LED_PIN_R, LEDC_CHANNEL_0_R);
  ledcSetup(LEDC_CHANNEL_1_G, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
  ledcAttachPin(LED_PIN_G, LEDC_CHANNEL_1_G);
  ledcSetup(LEDC_CHANNEL_2_B, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
  ledcAttachPin(LED_PIN_B, LEDC_CHANNEL_2_B);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Match the request
  int valR, valG, valB;
  String subStringR, subStringG, subStringB;
  int index = req.indexOf("/rgb/");
  if(index != -1){
    if(req.charAt(index+11)=='/'){
      subStringR = req.substring(index+5, index+7);
      subStringG = req.substring(index+7, index+9);
      subStringB = req.substring(index+9, index+11);
      Serial.println("R: " + subStringR);
      Serial.println("G: " + subStringG);
      Serial.println("B: " + subStringB);

      valR = subStringR.toInt();
      valG = subStringG.toInt();
      valB = subStringB.toInt();
      Serial.println("valR: " + String(valR));
      Serial.println("valG: " + String(valG));
      Serial.println("valB: " + String(valB));
      
    }
    else{
      Serial.println("Not terminated with /");
      client.stop();
      return;
    }
  }
  else {
    Serial.println("No /rgb/ found");
    client.stop();
    return;
  }

  // Set GPIOs according to the request
  // No check valid of the requested setting
  ledcAnalogWrite(LEDC_CHANNEL_0_R, valR);
  ledcAnalogWrite(LEDC_CHANNEL_1_G, valG);
  ledcAnalogWrite(LEDC_CHANNEL_2_B, valB);
  
  client.flush();

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIOs of RGB is now ";
  s += String(valR) +":" + String(valG) + ":" + String(valB);
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}

