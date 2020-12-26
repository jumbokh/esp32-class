 
#include <WiFi.h>
#include <WebServer.h>
#include <WiFiClient.h>
#include "OV2640.h"
#include "SimStreamer.h"
#include "OV2640Streamer.h"
#include "CRtspSession.h"
 
const char *ssid =     "YourSSID";         // Put your SSID here
const char *password = "YourPassword";      // Put your PASSWORD here
 
OV2640 cam;
 
WebServer server(80);
WiFiServer rtspServer(554);
 
void handle_jpg_stream(void)
{
  WiFiClient client = server.client();
  String response = "HTTP/1.1 200 OK\r\n";
  response += "Content-Type: multipart/x-mixed-replace; boundary=frame\r\n\r\n";
  server.sendContent(response);
 
  while (1)
  {
    cam.run();
    if (!client.connected())
      break;
    response = "--frame\r\n";
    response += "Content-Type: image/jpeg\r\n\r\n";
    server.sendContent(response);
 
    client.write((char *)cam.getfb(), cam.getSize());
    server.sendContent("\r\n");
    if (!client.connected())
      break;
  }
}
 
void handle_jpg(void)
{
  WiFiClient client = server.client();
  cam.run();
  if (!client.connected())
  {
    return;
  }
  String response = "HTTP/1.1 200 OK\r\n";
  response += "Content-disposition: inline; filename=capture.jpg\r\n";
  response += "Content-type: image/jpeg\r\n\r\n";
  server.sendContent(response);
  client.write((char *)cam.getfb(), cam.getSize());
}
 
void handleNotFound()
{
  String message = "Server is running!\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)   "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  server.send(200, "text/plain", message);
}
 
CStreamer *streamer;
 
void setup()
{
 
  Serial.begin(115200);
  cam.init(esp32cam_aithinker_config);
  IPAddress ip;
 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(F("."));
  }
  ip = WiFi.localIP();
  server.on("/", HTTP_GET, handle_jpg_stream);
  server.on("/jpg", HTTP_GET, handle_jpg);
  server.onNotFound(handleNotFound);
  server.begin();
  rtspServer.begin();
  streamer = new OV2640Streamer(cam);             // our streamer for UDP/TCP based RTP transport
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(ip);
  Serial.println("Use 'http://IP address/' to watch mjpeg stream");
  Serial.println("Use 'http://IP address/jpg' to see still jpg");
  Serial.println("Use RTRP:'IP address', URL:'/mjpeg/1' and port:554 to start rtsp stream");
}
 
void loop() {
 
  server.handleClient();
  uint32_t msecPerFrame = 100;
  static uint32_t lastimage = millis();
  // If we have an active client connection, just service that until gone
  streamer->handleRequests(0); // we don't use a timeout here,
  // instead we send only if we have new enough frames
  uint32_t now = millis();
  if (streamer->anySessions()) {
    if (now > lastimage + msecPerFrame || now < lastimage) { // handle clock rollover
      streamer->streamImage(now);
      lastimage = now;
 
      // check if we are overrunning our max frame rate
      now = millis();
      if (now > lastimage + msecPerFrame) {
        printf("warning exceeding max frame rate of %d ms\n", now - lastimage);
      }
    }
  }
  WiFiClient rtspClient = rtspServer.accept();
  if (rtspClient) {
    Serial.print("client: ");
    Serial.print(rtspClient.remoteIP());
    Serial.println();
    streamer->addSession(rtspClient);
  }
}
 
