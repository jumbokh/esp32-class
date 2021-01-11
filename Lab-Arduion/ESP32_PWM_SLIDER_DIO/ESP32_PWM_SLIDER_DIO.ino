/*
 * Mish Mash Labs
 * September 2020
 * Webserver with PWM Control of Brightness of LED
*/

// Import libraries that are used
#include <WiFi.h>
/*
 * You will need to download the .zip file for the following libraries from the links below
 * Install via Sketch > Include Library > Add .ZIP Library and browse to the download
 */
// https://github.com/me-no-dev/AsyncTCP
#include <AsyncTCP.h>
// https://github.com/me-no-dev/ESPAsyncWebServer
#include <ESPAsyncWebServer.h>

// Insert your own wifi network SSID and Password
const char* ssid = "my-ssid";
const char* password = "my-key";

const int ledPin = 4;

String pwmSliderValue = "0";

// Set Desired PWM Settings
const int frequencyHz = 5000;
const int pwmChannel = 0;
const int resolution = 8;

const char* INPUT_PARAMETER = "value";

// Instatiate the AsyncWebServer object on port 80
AsyncWebServer webServer(80);

// Declare the webpage
// HTML comments look like this <! comment in between here >
const char htmlCode[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <!  define meta data >
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <! define the style CSS of your page >
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h1 {font-size: 2.9rem;}
    h2 {font-size: 2.1rem;}
    p {font-size: 1.9rem;}
    body {max-width: 400px; margin:0px auto; padding-bottom: 30px;}
    .slider { -webkit-appearance: none; margin: 14px; width: 400px; height: 15px; border-radius: 5px; background: #39a6de; outline: none; -webkit-transition: .2s; transition: opacity .2s;}
    .slider::-webkit-slider-thumb {-webkit-appearance: none; appearance: none; width: 25px; height: 25px; border-radius: 12px; background: #f74d4d; cursor: pointer;}
    .slider::-moz-range-thumb { width: 25px; height: 25px; border-radius: 12px; background: #F74D4D; cursor: pointer; } 
  </style>
</head>

<body>
  <! Edit the pages your heading 1 >
  <h1>Mish Mash Labs</h1>

  <! Adding the logo here >
  <img src="https://yt3.ggpht.com/a/AATXAJxkbzn1yJWmRJRNOJ5uTRH4KDZxt761H4ADQIjz=s288-c-k-c0xffffffff-no-rj-mo">
  
  <! Edit the pages your heading 2 >
  <h2>ESP32 PWM Slider</h2>
  <h2>LED Brightness</h2>
  
  <! Displays the value of the slider >
  <p><span id="textSliderValue">%SLIDERVALUE%</span> &#37</p>
  <! displays the range of the slider 0 - 100 in steps of 1 >
  <p><input type="range" onchange="updateSliderPWM(this)" id="pwmSlider" min="0" max="100" value="%SLIDERVALUE%" step="1" class="slider"></p>
<script>
function updateSliderPWM(element) {
  var pwmSliderValue = document.getElementById("pwmSlider").value;
  document.getElementById("textSliderValue").innerHTML = pwmSliderValue;
  console.log(pwmSliderValue);
  var httpRequest = new XMLHttpRequest();
  httpRequest.open("GET", "/slider?value="+pwmSliderValue, true);
  httpRequest.send();
}
</script>
</body>
</html>
)rawliteral";

// Replaces the placeholder with the button in your web page
String updateButton(const String& var){
  if (var == "SLIDERVALUE"){
    return pwmSliderValue;
  }
  return String();
}

void setup(){
  // Begine Serial Communications over USB
  Serial.begin(115200);
  
  // configure LED PWM functionalitites
  // use ledcSetup(channel, frequency, resolution) to configure the PWM signal
  // ledcSetup(ESP PWM channel not GPIO pin, frequency in Hz, resolution (1-16 bit))
  ledcSetup(pwmChannel, frequencyHz, resolution);
  
  // attach the channel to the GPIO to be controlled
  /*
   * The PWM channel is not the same as a physical pin. 
   * The ESP32 contains 16 independent channels. 
   * Each of those can be assigned to any PWM-capable pin. 
   * This means that you can use any 16 GPIOs to generate PWM output.
   */
  // use ledcAttachPin(GPIO pin, PWM channel) to bind the GPIO number and the PWM channel number that you want to use
  ledcAttachPin(ledPin, pwmChannel);
  
  ledcWrite(pwmChannel, pwmSliderValue.toInt());

  // Connect to your Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print the IP Address of your device
  Serial.println(WiFi.localIP());

  // Detail the route for root / web page
  webServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", htmlCode, updateButton);
  });

  // Send a GET request to <ESP_IP>/slider?value=<inputMessage>
  webServer.on("/slider", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    // GET input1 value on <ESP_IP>/slider?value=<inputMessage>
    if (request->hasParam(INPUT_PARAMETER)) {
      inputMessage = request->getParam(INPUT_PARAMETER)->value();
      pwmSliderValue = inputMessage;
      ledcWrite(pwmChannel, pwmSliderValue.toInt());
    }
    else {
      inputMessage = "No message sent";
    }
    Serial.println(inputMessage);
    request->send(200, "text/plain", "OK");
  });
  
  // Start server (remembering its on port 80)
  webServer.begin();
}
  
void loop() {
  
}
