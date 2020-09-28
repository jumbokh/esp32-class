#include <WiFi.h>//wifi
#include <WiFiMulti.h>//多重連線
#include <HTTPClient.h>//瀏覽器
#include <ArduinoJson.h>//使用JSON函式庫

char SSID[] = "jumboap"; //請修改
char PASSWORD[] = "0953313123"; //請修改
char url[] = "http://opendata2.epa.gov.tw/AQI.json"; //讀取的網址
WiFiMulti WiFiMulti;//WiFiMulti是多點連線，可嘗試多個ssid

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("[SETUP] WAIT");
  WiFiMulti.addAP(SSID, PASSWORD);//加入一組WIFI AP
  for (int t = 4; t > 0; t--)
  {
    Serial.print(".");
    delay(1000);
  }
}

void loop()
{
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED))
  {
    Serial.println("Connected...");
    HTTPClient http;//啟動http client物件
    Serial.println("開始讀取資料");
    http.begin(url); //HTTP取得網頁內容

    Serial.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();//了解連線狀態

    Serial.println(httpCode);
    if (httpCode == HTTP_CODE_OK)
    {
      String payload = http.getString();//讀取網頁內容到payload
      Serial.print("payload=");
      //payload=payload.substring(0,200);//只擷取前面兩百個字
      //Serial.println(payload);
      DynamicJsonDocument AQJarray(payload.length() * 2);
      deserializeJson(AQJarray, payload);//解析payload為JSON Array格式
      for (int i = 0; i < AQJarray.size(); i++) {
        if (AQJarray[i]["SiteId"] == "54") {
          //抓取編號54號的站所(左營)
          String LinParkPM25 = AQJarray[i]["PM2.5"];
          String LinParkAQI = AQJarray[i]["AQI"];
          Serial.println("左營PM2.5：" + LinParkPM25+", AQI: "+LinParkAQI);
        }
      }
    }
    else {
      //讀取失敗
      Serial.println("[HTTP] GET... failed");
    }
    http.end();
  }
  delay(10000);
}
