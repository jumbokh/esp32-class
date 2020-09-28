/*------- --------- --------- --------- --------- --------- --------- --------- 
    Filename   : AT_BC26.cpp
    Author     : Samui Young
    Date       : 2019/09/16
    Disclaimer : This code is presented "as is" without any guarantees.
    Details    : comunicate with BC26 by AT command
--------- --------- --------- --------- --------- --------- --------- ---------
    2020/01/17 :
        -  001 : 
    2020/01/16 :
        -  001 : change serial port from Serial(for ESP8255) to Serial2(for ESP32S)
    2019/09/17 :
        -  001 : v0.0.1
    2019/09/16 :
        -  000 : new
--------- --------- --------- --------- --------- --------- --------- --------*/

/*------- --------- --------- --------- --------- --------- --------- --------- 
    header files
--------- --------- --------- --------- --------- --------- --------- --------*/
#include "AT_BC26.h"

/*------- --------- --------- --------- --------- --------- --------- --------- 
    macros
--------- --------- --------- --------- --------- --------- --------- --------*/



/*------- --------- --------- --------- --------- --------- --------- --------- 
    constant
--------- --------- --------- --------- --------- --------- --------- --------*/
const uint32_t  _timeWaitFirst = 500000;          // us, 0.5 sec, default waiting time for receiving first byte after AT command send
const uint32_t  _timeWaitAnswer = 10000000;       // us,  10 sec, defualt waiting time for receiving specific answer

/*------- --------- --------- --------- --------- --------- --------- --------- 
    variables
--------- --------- --------- --------- --------- --------- --------- --------*/
uint32_t _baudPeriod;         // us, period of a baud
uint32_t _timeWaitNext;       // us, waiting time for receiving next continuous byte

String _history;              // history of operation
String _debugMsg;             // debug message of operation
String _errorMsg;             // error message from AT+QIGETERROR

bool historyMode = true;      // record history, default is true
bool debugMode = false;      // debug mode, default is false

/*------- --------- --------- --------- --------- --------- --------- --------- 
    constructor and destructor
--------- --------- --------- --------- --------- --------- --------- --------*/
AT_BC26::AT_BC26()
{
  _debugMsg = "";
  _history = "";
  _errorMsg = "";
  historyMode = true;
  debugMode = false;

  _baudPeriod = (uint32_t)((double)1000000 / 115200 + 0.5);  // in microseconds
  _timeWaitNext = (uint32_t)((double)1000000 * 10 * 128 / 115200 + 0.5);  // in microseconds
}

AT_BC26::~AT_BC26(){}

//------- --------- --------- --------- --------- --------- --------- --------- 
//  AT_BC26::setSpeed()
//    serialSpeed : baud rate of Serial to set
//------- --------- --------- --------- --------- --------- --------- --------- 
void AT_BC26::setSpeed(int32_t serialSpeed)
{
	if (serialSpeed == 0) serialSpeed = 115200;

  _baudPeriod = (uint32_t)((double)1000000 / serialSpeed + 0.5);  // in microseconds
  _timeWaitNext = (uint32_t)((double)1000000 * 10 * 128 / serialSpeed + 0.5);  // in microseconds
  // 1000000(us/sec) * 10(baud/byte) * 128(bytes) / serialSpeed + 0.5

  Serial2.flush();
  Serial2.begin(serialSpeed);
}

//------- --------- --------- --------- --------- --------- --------- --------- 
//  AT_BC26::receive() : 
//    timeLimit : limitation of time out, in microseconds
//------- --------- --------- --------- --------- --------- --------- --------- 
String AT_BC26::receive(uint32_t timeLimit)
{
  uint32_t timeStart;
  uint32_t timeElapse;

  String response = "";

  //----- //------- //------- //------- //------- //------- 
  // wait for first contact
  if (debugMode) _debugMsg += "[" + AT_BC26::microSecond(micros()) + "]  waiting\r\n";
  timeStart = micros();
  while ((micros() - timeStart < timeLimit) && (Serial2.available() < 1)) {}
  timeElapse = micros() - timeStart;

  //if (debugMode) _debugMsg += "[" + AT_BC26::microSecond(timeStart) + "><" + AT_BC26::microSecond(timeStart + timeElapse) + ">\r\n";

  //----- //------- //------- //------- //------- //------- 
  // read data from serial port
  if (debugMode) _debugMsg += "[" + AT_BC26::microSecond(micros()) + "]  reading\r\n";
  response = "";
  timeStart = micros();
  do
  {
    if (Serial2.available() > 0)
    {
      response += (char)Serial2.read();
      timeStart = micros();
    }
  } while (micros() - timeStart < _timeWaitNext);
  timeElapse = micros() - timeStart;

  if (historyMode) _history += response;
  if (debugMode) _debugMsg += response + (response.length() > 0 ? "\r\n[" : "[") + AT_BC26::microSecond(timeStart + timeElapse) + "]  read stop\r\n";

  return response;

}

//------- --------- --------- --------- --------- --------- --------- --------- 

String AT_BC26::receive()
{
  return AT_BC26::receive(_timeWaitFirst);
}

//------- --------- --------- --------- --------- --------- --------- --------- 
String AT_BC26::receive(String answer, uint32_t timeout)
{
  uint32_t timeStart;

  String response = "";

  timeStart = micros();
  do
  {
    response += AT_BC26::receive(_timeWaitFirst);
    if (response.indexOf("ERROR") != -1) break;
  } while ((response.indexOf(answer) == -1) && (micros() - timeStart < timeout));

  return response;
}

//------- --------- --------- --------- --------- --------- --------- --------- 
String AT_BC26::receive(String answer)
{
  return AT_BC26::receive(answer, _timeWaitAnswer);
}

//------- --------- --------- --------- --------- --------- --------- --------- 
//  AT_BC26::send() : 
//    ATcommand : request AT command
//    timeLimit : limitation of time out, in microseconds
//------- --------- --------- --------- --------- --------- --------- --------- 
String AT_BC26::send(String ATcommand, uint32_t timeLimit)
{

  uint32_t timeStart;
  uint32_t timeElapse;

  String response = "";
  String history = "";
  //String debugMsg = "";

  //----- //------- //------- //------- //------- //------- 
  // read and clear previous response
  history = "[" + AT_BC26::microSecond(micros()) + "]  previous\r\n";
  while (Serial2.available() > 0)
  {
    response += (char)Serial2.read();
  }
  if (response.length() > 0)
  {
    if (historyMode) _history += response + "\r\n";
    if (debugMode) _debugMsg += history + response + "\r\n[" + AT_BC26::microSecond(micros()) + "]  previous(" + String(response.length()) + ")\r\n";
  }

  //----- //------- //------- //------- //------- //------- 
  // send AT command
  history = AT_BC26::microSecond(micros());

  Serial2.println(ATcommand);
  Serial2.flush();

  if (historyMode) _history += "[" + history + "> " + ATcommand + "\r\n";
  if (debugMode) _debugMsg += "[" + history + "> " + ATcommand + "\r\n";

  //----- //------- //------- //------- //------- //------- 
  // clear input buffer of Serial for strange result when no response after 2nd request
  timeStart = micros();
  while ((micros() - timeStart < _baudPeriod * 10) && (Serial2.available() < 1)) {}
  timeElapse = micros() - timeStart;
  if (Serial2.available() > 0)
  {
    if (historyMode) _history += "(" + AT_BC26::microSecond(micros()) + ">>>\r\n";
    while(Serial2.available() > 0)
    {
      if (historyMode) _history += String(Serial2.read()) + " ";
    }
    if (historyMode) _history += "<" + AT_BC26::microSecond(micros()) + ")))\r\n";;
  }

  //----- //------- //------- //------- //------- //------- 
  // read data from serial port
  response = AT_BC26::receive(timeLimit);

  return response;

}

//------- --------- --------- --------- --------- --------- --------- --------- 
String AT_BC26::send(String ATcommand)
{
  return AT_BC26::send(ATcommand, _timeWaitFirst);
}

//------- --------- --------- --------- --------- --------- --------- --------- 
String AT_BC26::send(String ATcommand, String answer, uint32_t timeout)
{
  uint32_t timeStart;
  String response = "";

  response = AT_BC26::send(ATcommand, _timeWaitFirst);

  timeStart = micros();
  do
  {
    response += AT_BC26::receive(_timeWaitFirst);
    if (response.indexOf("ERROR") != -1) break;
  } while ((response.indexOf(answer) == -1) && (micros() - timeStart < timeout));


  return response;

}

//------- --------- --------- --------- --------- --------- --------- --------- 
String AT_BC26::send(String ATcommand, String answer)
{
  return AT_BC26::send(ATcommand, answer, _timeWaitAnswer);
}

//------- --------- --------- --------- --------- --------- --------- --------- 
//  AT_BC26::getError()
//------- --------- --------- --------- --------- --------- --------- --------- 
String AT_BC26::getError()
{
  String result = _errorMsg;
  _errorMsg = "";
  return result;
}

//------- --------- --------- --------- --------- --------- --------- --------- 
//  AT_BC26::history()
//------- --------- --------- --------- --------- --------- --------- --------- 
String AT_BC26::history()
{
  String result = _history;
  _history = "";
  return result;
}

//------- --------- --------- --------- --------- --------- --------- --------- 
//  AT_BC26::debugMsg()
//------- --------- --------- --------- --------- --------- --------- --------- 
String AT_BC26::debugMsg()
{
  String result = _debugMsg;
  _debugMsg = "";
  return result;
}

//------- --------- --------- --------- --------- --------- --------- ----------
//  milliSecond()
//------- --------- --------- --------- --------- --------- --------- ----------
String AT_BC26::milliSecond(uint32_t mS)
{
  uint32_t temp;
  String result;

  temp = mS;                  // temp : ms

  result = "000" + String(temp % 1000);
  result = "." + result.substring(result.length() - 3);

  temp = temp / 1000;         //  temp : sec

  result = "00" + String(temp % 60) + result;
  result = ":" + result.substring(result.length() - 6);

  temp = temp / 60;           // temp : min

  result = "00" + String(temp % 60) + result;
  result = ":" + result.substring(result.length() - 9);

  temp = temp / 60;           // temp : hr

  result = "00" + String(temp % 24) + result;
  result = " " + result.substring(result.length() - 12);

  temp = temp / 24;           // temp : day

  result = "00" + String(temp) + result;
  result = result.substring(result.length() - 15) + " 000";

  /*
  String result = "0000000000" + String(mS);
  result = result.substring(result.length() - 10);
  result
    = ""
    + result.substring(0,1) + ","
    + result.substring(1,4) + ","
    + result.substring(4,7) + "."
    + result.substring(7)
    ;
  */

  return result;
}

//------- --------- --------- --------- --------- --------- --------- ----------
//  microSecond()
//------- --------- --------- --------- --------- --------- --------- ----------
String AT_BC26::microSecond(uint32_t uS)
{
  uint32_t temp;
  String result;

  temp = uS;                  // temp : us

  result = "000" + String(temp % 1000);
  result = " " + result.substring(result.length() - 3);

  temp = temp / 1000;         //  temp : sec

  result = "000" + String(temp % 1000) + result;
  result = "." + result.substring(result.length() - 7);

  temp = temp / 1000;         //  temp : sec

  result = "00" + String(temp % 60) + result;
  result = ":" + result.substring(result.length() - 10);

  temp = temp / 60;           // temp : min

  result = "00" + String(temp % 60) + result;
  result = ":" + result.substring(result.length() - 13);

  temp = temp / 60;           // temp : hr

  result = "00" + String(temp % 24) + result;
  result = " " + result.substring(result.length() - 16);

  temp = temp / 24;           // temp : day

  result = "00" + String(temp) + result;
  result = result.substring(result.length() - 19);

  /*
  String result = "0000000000" + String(uS);
  result = result.substring(result.length() - 10);
  result
    = ""
    + result.substring(0,1) + ","
    + result.substring(1,4) + "."
    + result.substring(4,7) + " "
    + result.substring(7)
    ;
  */

  return result;
}


