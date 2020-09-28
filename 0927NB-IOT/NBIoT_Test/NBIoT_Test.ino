/*
 * ESP32輔助版說明：https://youyouyou.pixnet.net/blog/post/120569425
 * NBIOT測試網站：http://av119.ddns.net:8088/
 */
#include "src/AT_BC26/AT_BC26.h"//NO-IOT聯發科的晶片//聯發科NBIOT晶片函式庫
#include <SimpleDHT.h>
#include <TimeLib.h>//搜尋timekeeping，與中華電信時間校正用
#include <Wire.h>//板上的燈號

const String host = "av119.ddns.net";//送資料到那個網址，也可用 ip
const String port = "8089";
const String SIMPIN = "0000";//sim code 中華電信預設 0000
const String APN = "internet.iot";      //  for CHT 中華電信
//const String APN = "nbiot";             //  for FET 遠傳
const String IDSN = "jumbokh";        //設定您的機器編號
const bool _debug = true;
int DHTPIN = 13;
SimpleDHT11 dht11(DHTPIN);

//------- --------- --------- --------- --------- ---------
//版子上燈號的i2c設定
//------- --------- --------- --------- --------- ---------
#define   addrPCF8574         0x20
#define   addrPCF8574A        0x38
byte addrLED = addrPCF8574;

const byte led2_1 = 0b00000001;        //  ledSeg0,板上燈號的位置
const byte led2_2 = 0b00000010;        //  ledSeg1
const byte led2_3 = 0b00000100;        //  ledSeg2
const byte led2_4 = 0b00001000;        //  ledSeg3
const byte led2_5 = 0b00010000;        //  ledSeg4
const byte led3   = 0b00100000;         //  red, ledErr
const byte led4   = 0b01000000;         //  green, ledACT
const byte led5   = 0b10000000;         //  blue
const byte ledAll = 0b11111111;

const byte ledTurnOff = 0x00;
const byte ledTurnOn = 0x01;
const byte ledSwitch = 0xFF;

byte ledSeg0 = led2_1;
byte ledSeg1 = led2_2;
byte ledSeg2 = led2_3;
byte ledSeg3 = led2_4;
byte ledSeg4 = led2_5;
byte ledErr = led3;
byte ledACT = led4;


//------- --------- --------- --------- --------- ---------
//設定NBIOT BC26模組
//------- --------- --------- --------- --------- ---------
AT_BC26 bc26;//建立bc26物件
bool bc26SendOK = false;//假設傳送不成功
int BC26resetPIN = 14;     //  IO14(HS2_CLK)

//------- --------- --------- ---------
//  time to send data to host
//------- --------- --------- ---------
unsigned long timeLastSend = 0;                             //  ms, last data sent time

//------- --------- --------- ---------
//  default ssID, password, host IP, and report time period
//------- --------- --------- ---------


//  sender status
String snStatus = "";

//  serial number of data after boot
unsigned long dataSN = 0;

//  error count for sending data immediately
unsigned long errorCount = 0;

//  secret
String secret = "000000";

//  data to be sent to host by BC26 TCP transmition
String PayLoad = "";

//------- --------- --------- ---------
//  Absolute Zero -273.15 Celsius
//------- --------- --------- ---------
const float AbsZero = -273.15;

//------- --------- --------- --------- --------- ---------
//  error code
//------- --------- --------- --------- --------- ---------
int errorCode = 0;

//------- --------- --------- ---------
//  error flag
//------- --------- --------- ---------
byte errorFlag = 0x00;
const byte errFlagTS = 3;  //0x01;
const byte errFlagWiFi = 4;  //0x02;
const byte errFlagINet = 5;  //0x04;
const byte errFlagHost = 6;  //0x08;

//
const int delayErr = 300;

//  error retry count
byte retryCount = 3;

//  flag to go on program
bool GoOn = true;

//======= ========= ========= ========= ========= ========= ========= =========
//  Function declaration
//======= ========= ========= ========= ========= ========= ========= =========
void setup();
void loop();
unsigned long loopDelay(unsigned long loopStart, unsigned long loopPeriod);
void LEDop(byte ledNum, byte op);
void LEDon(byte ledNum);
void LEDoff(byte ledNum);
void LEDsw(byte ledNum);
void LEDflash(byte ledNum, int times, int period);
void LEDrssi(int rssi);
String parmParse(String parameters, String parmKey, String parmEnd);
String parmParse(String parameters, String parmKey);
String parmParse(String parameters, String delimiter, int index);
String leadingZeros(int value, int digits);


//======= ========= ========= ========= ========= ========= ========= =========
//  setup
//======= ========= ========= ========= ========= ========= ========= =========
void setup()
{
  //----- --------- --------- --------- --------- ---------
  //  reset BC26
  //----- --------- --------- --------- --------- ---------
  pinMode(BC26resetPIN, OUTPUT);//將BC26重開
  digitalWrite(BC26resetPIN, HIGH);
  digitalWrite(BC26resetPIN, LOW);

  //----- --------- --------- --------- --------- ---------
  //----- --------- --------- --------- --------- ---------
  if (_debug)
  {
    Serial.begin(115200);
    Serial.println();
    Serial.println();
    Serial.println("============================================================");
    Serial.println("Project : ESProMatrix-BC26");
    Serial.println("Date    : 2020/04/30");
    Serial.println("Version : 0.0.1");
    Serial.println("========================= Start up =========================");
  }


  /*
    //----- --------- --------- --------- --------- ---------
    //  disable WiFi of ESP32
    //----- --------- --------- --------- --------- ---------
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);          //  turn off WiFi
    WiFi.forceSleepBegin();       //  turn off WiFi
  */

  //----- --------- --------- --------- --------- ---------
  //  setup Wire for LCD & LED ，192-225 測燈號是否正常
  //----- --------- --------- --------- --------- ---------
  Wire.begin(26, 27);


  //----- --------- --------- --------- --------- ---------
  //  show LED 1 by 1
  //----- --------- --------- --------- --------- ---------
  int delayTime = 200;
  LEDoff(ledAll);
  delay(delayTime);

  byte ledShow[8] = {led3, led4, led5, ledSeg0, ledSeg1, ledSeg2, ledSeg3, ledSeg4};
  for (int i = 0; i < 8; i++)
  {
    LEDoff(ledAll);
    LEDon(ledShow[7 - i]);
    delay(delayTime);
  }
  for (int i = 1; i < 8; i++)
  {
    LEDoff(ledAll);
    LEDon(ledShow[i]);
    delay(delayTime);
  }
  LEDoff(ledAll);

  //----- --------- --------- --------- --------- ---------
  //  flash all LED 3 times
  //----- --------- --------- --------- --------- ---------
  LEDoff(ledAll);
  LEDflash(ledAll, 3, delayTime);
  LEDoff(ledAll);

} //  void setup()


//======= ========= ========= ========= ========= ========= ========= =========
//  loop
//======= ========= ========= ========= ========= ========= ========= =========
void loop()
{

  delay(30000);//NB-IOT 不能太常傳
  if (_debug) Serial.printf("======================== Loop start ========================%d\n", retryCount);

  String lcdMsg;

  //----- --------- --------- --------- --------- ---------
  //  Reading temperature or humidity takes about 250 milliseconds!
  //  Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  //----- --------- --------- --------- --------- ---------

  byte celsius = 0;//246-252，抓DHT11 的溫度
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&celsius, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err); delay(1000);
    return;
  }


  //  Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(celsius)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    //delay(1000);
    //return;
  }

  if (_debug)
  {
    Serial.print(F("Humidity: "));
    Serial.print(humidity);
    Serial.print(F("%  Temperature: "));
    Serial.print(celsius);
    Serial.print(F("°C "));
  }

  retryCount--;

  //===== ========= ========= ========= ========= ========= =========
  //  comunicate with BC26
  //===== ========= ========= ========= ========= ========= =========
  if (_debug)
  {
    Serial.println("---------------- start comunicate with BC26 ----------------");
    Serial.flush();
  }

  bc26.historyMode = true;
  bc26.setSpeed(115200);

  unsigned long timeStart;
  unsigned long timeToSend = 0;
  unsigned long timeToReset = 0;

  String history = "";
  String debugMsg = "";
  String response = "";
  String data = "";

  //----- --------- --------- ---------
  //  dummy command to clear response for last Serial.print before set baudrate to 115200
  //----- --------- --------- ---------

  response = bc26.send("ATE1");//開始跟 BC26溝通

  history = bc26.history();
  if (_debug) Serial.println(history);

  if ((response.indexOf("OK") == -1) && (response.indexOf("ERROR") == -1))
  {
    return;
  }

  delay(1000);

  response = bc26.send("AT+QCCID");

  history = bc26.history();
  if (_debug) Serial.println(history);

  if (response.indexOf("ERROR") != -1)
  {
    GoOn = false;
  }
  else if (response.indexOf("OK") != -1)
  {

  }


  if (!GoOn) return;
  delay(1000);

  //----- --------- --------- ---------
  //  check PIN
  //----- --------- --------- ---------


  response = bc26.send("AT+CPIN?");

  history = bc26.history();
  if (_debug) Serial.println(history);

  if (response.indexOf("SIM PIN") != -1)
  {
    response = bc26.send("AT+CPIN=\"" + SIMPIN + "\"");
    delay(100);
    response = bc26.send("AT+CPIN?");
  }

  response.replace("\r", "");

  if (response.indexOf("SIM PIN") != -1) return;
  delay(1000);

  //  //----- --------- --------- ---------
  //  //  check APN
  //  //----- --------- --------- ---------
  //  lcd.setCursor(0, 0);
  //  lcd.print("AT+QCGDEFCONT?  ");
  //
  //  timeStart = millis();
  //  while (true)
  //  {
  //    response = bc26.send("AT+QCGDEFCONT?");
  //    response = bc26.receive("+QCGDEFCONT:");
  //    if (response.indexOf("ERROR") != -1) bc26.send("AT+QIGETERROR");
  //
  //    history = bc26.history();
  //    if (_debug) Serial.println(history);
  //    if (_debug) Serial.println("(APN=\"" + APN + "\"@" + String(response.indexOf(APN)) + ")");
  //
  //    response.replace("\r", "");
  //    lcdMsg = parmParse(response, "+QCGDEFCONT:");
  //    lcdMsg = parmParse(lcdMsg, ",", 1);
  //    lcdMsg = ("                " + lcdMsg);
  //    lcdMsg = lcdMsg.substring(lcdMsg.length() - 16);
  //    lcd.setCursor(0, 1);
  //    lcd.print(lcdMsg);
  //
  //    if (response.indexOf(APN) != -1)
  //    {
  //      break;
  //    }
  //    if (millis() - timeStart > 3000) return;
  //
  //    response = bc26.send("AT+QCGDEFCONT=\"IPV4V6\",\"" + APN + "\"");
  //    if (response.indexOf("ERROR") != -1) bc26.send("AT+QIGETERROR");
  //
  //    history = bc26.history();
  //    if (_debug) Serial.println(history);
  //  }
  //  delay(1000);

  //----- --------- --------- ---------
  //  get signal strength form BC26
  //----- --------- --------- ---------

  int32_t rssi = -9999;           //  -9999 means no signal

  timeStart = millis();
  while (true)
  {
    response = bc26.send("AT+CESQ");
    if (response.indexOf("ERROR") != -1) bc26.send("AT+QIGETERROR");

    history = bc26.history();
    if (_debug) Serial.println(history);

    //404-464  calculate rssi問基地台訊號是否好不好
    response.replace("\r", "");
    data = parmParse(response, "+CESQ: ", ",");

    if (response.indexOf("ERROR") != -1)
    {
      lcdMsg = "ERROR";
    }
    else if (data == "99")      //  got answer "99" of AT+CESQ from BC26
    {
      lcdMsg = "no signal";
    }
    else if (data == "0")      //  got answer "0" of AT+CESQ from BC26
    {
      lcdMsg = "signal too weak";
    }
    else                        //  got answer of AT+CESQ from BC26
    {
      rssi = data.toInt() - 110;
      lcdMsg = "RSSI: " + String(rssi) + "dB";
    }
    LEDrssi(rssi);

    if (millis() - timeStart > 3000)
    {
      //if (errorFlag == 0) errorFlag = stepNum;
      LEDon(ledErr);
      return;
    }

    if (rssi == -9999)
    {
      delay(500);
    }
    else
    {
      break;
    }
  }

  delay(1000);


  //----- --------- --------- ---------
  //  check EPS Network Registration Status
  //----- --------- --------- ---------

  timeStart = millis();
  while (true)//跟基地台註冊
  {
    response = bc26.send("AT+CEREG?");
    response.replace("\r", "");

    history = bc26.history();
    if (_debug) Serial.println(history);

    if (response.indexOf("+CEREG: 0,1") != -1)
    {
      delay(2000);
      break;
    }

    if (response.indexOf("ERROR") != -1)
    {
      bc26.send("AT+QIGETERROR");

      history = bc26.history();
      if (_debug) Serial.println(history);

      lcdMsg = "ERROR";
    }
    else
    {
      lcdMsg = "+CEREG:" + parmParse(response, "+CEREG:");
    }
    lcdMsg = ("                " + lcdMsg).substring(lcdMsg.length());

    if (millis() - timeStart > 5000)
    {
      return;
    }
    else
    {
      delay(1000);
    }
  }

  delay(1000);

  //----- --------- --------- ---------
  //494-574  get time from BC26，時間校正
  //----- --------- --------- ---------

  String dateTime;
  String keyParse;

  response = bc26.send("AT+CCLK?");
  if (response.indexOf("ERROR") != -1) bc26.send("AT+QIGETERROR");
  response.replace("\r", "");

  history = bc26.history();
  if (_debug) Serial.println(history);

  //  get year part
  keyParse = "+CCLK:";
  data = parmParse(response, keyParse, "/");
  keyParse += data + "/";
  data.trim();
  dateTime = data;            //  year
  if (dateTime == "")         //  got no answer of AT+CCLK? from BC26
  {
    //  if can't get datetime from BC26 by AT+CCLK?, get datetime from now() of TimeLib
    time_t unixTime = now();

    dateTime
      = leadingZeros(year(unixTime), 4)
        + leadingZeros(month(unixTime), 2)
        + leadingZeros(day(unixTime), 2)
        + leadingZeros(hour(unixTime), 2)
        + leadingZeros(minute(unixTime), 2)
        + leadingZeros(second(unixTime), 2);

    dateTime += leadingZeros(millis() % 1000, 3);
  }
  else                        //  got answer of AT+CCLK? from BC26
  {
    //  get month part
    data = parmParse(response, keyParse, "/");
    keyParse += data + "/";
    dateTime += leadingZeros(data.toInt(), 2);

    //  get day part
    data = parmParse(response, keyParse, ",");
    keyParse += data + ",";
    dateTime += leadingZeros(data.toInt(), 2);

    //  get hour part
    data = parmParse(response, keyParse, ":");
    keyParse += data + ":";
    dateTime += leadingZeros(data.toInt(), 2);

    //  get minute part
    data = parmParse(response, keyParse, ":");
    keyParse += data + ":";
    dateTime += leadingZeros(data.toInt(), 2);

    //  get second part
    data = parmParse(response, keyParse, "G");
    dateTime += leadingZeros(data.toInt(), 2);

    //  millisecond part
    dateTime += leadingZeros(int(millis() % 1000), 3);

    //
    setTime
    (
      dateTime.substring(8, 8 + 2).toInt(),       //  hour
      dateTime.substring(10, 10 + 2).toInt(),     //  minute
      dateTime.substring(12, 12 + 2).toInt(),     //  second
      dateTime.substring(6, 6 + 2).toInt(),       //  day
      dateTime.substring(4, 4 + 2).toInt(),       //  month
      dateTime.substring(0, 0 + 4).toInt()        //  year
    );

  }

  delay(1000);

  lcdMsg = dateTime;
  //lcdMsg = ("                " + lcdMsg).substring(lcdMsg.length());

  //----- --------- --------- ---------
  //  prepare data to send
  //----- --------- --------- ---------
  String dataSNhex = String(dataSN, HEX);
  dataSNhex.toUpperCase();

  String PayLoadPrev = PayLoad;//IDSN 每個人的編號,rssi 訊號強度
  PayLoad
    = String("av119")
      + "," + IDSN
      + "," + dateTime
      + "," + celsius
      + "C," + humidity
      + "H," + dataSNhex
      + "," + snStatus
      + "," + String(abs(rssi))
      ;

  //----- --------- --------- ---------
  //  send data to server by BC26
  //----- --------- --------- ---------

  data = "";

  unsigned long timeElapse = millis() - timeLastSend;
  if (timeElapse >= timeToSend)
  {
    delay(200);

    //--- --------- --------- ---------
    //  open connection to server
    //--- --------- --------- ---------

    response = bc26.send("AT+QIOPEN=1,0,\"TCP\",\"" + host + "\"," + port, "+QIOPEN: 0,0");//連線到伺服器
    if (response.indexOf("ERROR") != -1) bc26.send("AT+QIGETERROR");

    history = bc26.history();
    if (_debug) Serial.println(history);

    GoOn = false;
    timeStart = millis();
    while (millis() - timeStart < 3000)//等候3秒，看伺服器是否回覆
    {
      if (response.indexOf("+QIOPEN: 0,0") == -1)
      {
        response = bc26.receive("+QIOPEN: 0,0");
        history = bc26.history();
        if (_debug) Serial.println(history);
      }
      else //  connection open OK
      {
        GoOn = true;
        break;
      }
    }

    if (!GoOn) return;
    delay(1000);

    //--- --------- --------- ---------
    //  send data to server
    //--- --------- --------- ---------

    response = bc26.send("AT+QISEND=0," + String(PayLoad.length()) + ",\"" + PayLoad + "\"", "SEND OK");//送資料到伺服器
    if (response.indexOf("ERROR") != -1) bc26.send("AT+QIGETERROR");

    history = bc26.history();
    if (_debug) Serial.println(history);

    delay(1000);


    /*
      //--- --------- --------- --------- --------- ---------
      //  read feedback data from host，等伺服器回覆
      //--- --------- --------- --------- --------- ---------
      //if (snStatus == "boot")
      if (dataSN == 0)
      {
      snStatus = "";
      if (response.indexOf("+QIURC: \"recv\",0") == -1)
      {
        response = bc26.receive("+QIURC: \"recv\",0");

        history = bc26.history();
        if (_debug) Serial.println(history);
      }
      if (response.indexOf("+QIURC: \"recv\",0") != -1)
      {
        response = bc26.send("AT+QIRD=0,512", "+QIRD");

        history = bc26.history();
        if (_debug) Serial.println(history);

        String key = parmParse(response, "+QIRD:");
        if (key != "")
        {
          key = "+QIRD:" + key + "\n";
          data = parmParse(response, key);
        }
      }
      }
    */

    response = bc26.send("AT+QICLOSE=0", "CLOSE OK");//bc26與伺服器斷線
    if (response.indexOf("ERROR") != -1) bc26.send("AT+QIGETERROR");

    history = bc26.history();
    if (_debug) Serial.println(history);

    timeLastSend = millis();

    dataSN++;
    bc26SendOK = true;
  }

  if (_debug)
  {
    Serial.println("\r\n---------------- stop  comunicate with BC26 ----------------");
    Serial.println("time: " + dateTime);
  }

} //  void loop()


//======= ========= ========= ========= ========= ========= ========= =========
//  自定義函數
//======= ========= ========= ========= ========= ========= ========= =========

//------- --------- --------- --------- --------- --------- --------- ----------
//  loop delay
//------- --------- --------- --------- --------- --------- --------- ----------
unsigned long loopDelay(unsigned long loopStart, unsigned long loopPeriod)
{
  unsigned long loopRemain = 0;
  unsigned long loopElapse = millis() - loopStart;
  if (_debug) Serial.print("time elapse: " + String(loopElapse));
  if (loopElapse < loopPeriod)
  {
    loopRemain = loopPeriod - loopElapse;
    if (_debug) Serial.print(" , time remain: " + String(loopRemain));
    delay(loopRemain);
  }
  if (_debug) Serial.println();
  return loopRemain;
}


//------- --------- --------- --------- --------- --------- --------- ----------
//  LED operation : turn LED on/off, switch LED on/off, flash LED
//------- --------- --------- --------- --------- --------- --------- ----------
void LEDop(byte ledNum, byte op)
{
  //  op =  0x00 : turn off
  //  op =  0x01 : turn on
  //  op =  0xFF : switch on/off

  byte ledInput = 0;
  byte ledOutput = 0;
  String msg = "";
  byte opLED1 = ledNum & ledACT;

  Wire.requestFrom((int)addrLED, 1);
  while (Wire.available())
  {
    ledInput = Wire.read();

    switch (op)
    {
      case ledTurnOff:
        //  turn LED off
        ledOutput = ledInput | ledNum;
        msg = "Trun Off ";
        break;
      case ledTurnOn:
        //  turn LED on
        ledOutput = ledInput & ~ledNum;
        msg = "Trun On ";
        break;
      case ledSwitch:
        //  switch LED on/off
        ledOutput = ledInput ^ ledNum;
        msg = "Switch ";
        break;
      default:
        msg = "not command ";
        break;
    } //  switch (op)

    Wire.beginTransmission((int)addrLED);
    Wire.write(ledOutput);
    Wire.endTransmission();
  } //  while (Wire.available())

} //  void LEDop(byte ledNum, byte op)

void LEDon(byte ledNum)
{
  LEDop(ledNum, ledTurnOn);
} //  void LEDon(byte ledNum)

void LEDoff(byte ledNum)
{
  LEDop(ledNum, ledTurnOff);
} //  void LEDoff(byte ledNum)

void LEDsw(byte ledNum)
{
  LEDop(ledNum, ledSwitch);
} //  void LEDsw(byte ledNum)

void LEDflash(byte ledNum, int times, int period)
{
  LEDoff(ledNum);
  delay(period);
  for (int i = 0 ; i < times; i++)
  {
    LEDon(ledNum);
    delay(period);
    LEDoff(ledNum);
    delay(period);
  }
}

void LEDrssi(int32_t rssi)
{
  if (rssi > -65)
  {
    LEDon(ledSeg0 + ledSeg1 + ledSeg2 + ledSeg3 + ledSeg4);
  }
  else if (rssi > -75)
  {
    LEDon(ledSeg0 + ledSeg1 + ledSeg2 + ledSeg3);
    LEDoff(ledSeg4);
  }
  else if (rssi > -85)
  {
    LEDon(ledSeg0 + ledSeg1 + ledSeg2);
    LEDoff(ledSeg3 + ledSeg4);
  }
  else if (rssi > -95)
  {
    LEDon(ledSeg0 + ledSeg1);
    LEDoff(ledSeg2 + ledSeg3 + ledSeg4);
  }
  else if (rssi > -105)
  {
    LEDon(ledSeg0);
    LEDoff(ledSeg1 + ledSeg2 + ledSeg3 + ledSeg4);
  }
  else
  {
    LEDoff(ledSeg0 + ledSeg1 + ledSeg2 + ledSeg3 + ledSeg4);
  }
}

//------- --------- --------- --------- --------- --------- --------- ----------
//  show message on LCM
//------- --------- --------- --------- --------- --------- --------- ----------






//------- --------- --------- --------- --------- --------- --------- ----------
//  parameter parse
//------- --------- --------- --------- --------- --------- --------- ----------
String parmParse(String parameters, String parmKey, String parmEnd)
{
  int from = -1;
  int to = -1;

  from = parameters.indexOf(parmKey);
  if (from < 0) return "";
  from = from + parmKey.length();
  to = parameters.indexOf(parmEnd, from);
  return parameters.substring(from, to);

  //  parameters = "+CPIN: READY";
  //  parmKey = "+CPIN:";
  //  parmEnd = "\n";
  //    to=0: "+CPIN:"
  //    to=-1: " READY"
  //    to=parameters.length(): " READY"
  //    to=parameters.length() - 1: " READY"
}

//------- --------- --------- --------- --------- --------- --------- ----------
String parmParse(String parameters, String parmKey)
{
  String parmEnd = "\n";
  String temp = parameters;
  temp.replace("\r", "");
  return parmParse(temp, parmKey, parmEnd);
}

//------- --------- --------- --------- --------- --------- --------- ----------
String parmParse(String parameters, String delimiter, int index)
{
  int from = 0;
  int next = -1;
  int count = 0;
  String result = "";

  for (count = 0; count < index + 1; count++)
  {
    from = next + 1;
    next = (parameters + delimiter).indexOf(delimiter, from);
    if (next < 0) break;
  }

  if (count == index + 1)
  {
    result = parameters.substring(from, next);
  }

  return result;
}

//------- --------- --------- --------- --------- --------- --------- ----------

String shortenMac(String mac, int newLength)
{
  if (mac == "") return "";

  const String hex = "0123456789ABCDEF";
  int bytes = (mac.length() - 1) / 16 + 1;
  int start = 0;

  mac.toUpperCase();

  for (int i = 0; i < bytes; i++)
  {
    start += hex.indexOf(mac.substring(i, i + 1));
  }

  return (mac + mac).substring(start, start + newLength);
}

//------- --------- --------- --------- --------- --------- --------- ----------
//  convert int to String with leading zero
//------- --------- --------- --------- --------- --------- --------- ----------
String leadingZeros(int value, int digits)
{
  String text = String(value);
  text.replace("-", "");
  for (int i = text.length(); i < digits; i++)
  {
    text = "0" + text;
  }
  if (value < 0)
  {
    text = "-" + text;
  }
  return text;
}

//------- --------- --------- --------- --------- --------- --------- ----------
//  convert int to hexadecimal string with number of digits
//------- --------- --------- --------- --------- --------- --------- ----------
String int2Hex(int integer, int digits)
{
  String hex = String(integer, HEX);
  hex.toUpperCase();
  for (int i = hex.length(); i < digits; i++)
  {
    hex = "0" + hex;
  }
  return hex;

}
