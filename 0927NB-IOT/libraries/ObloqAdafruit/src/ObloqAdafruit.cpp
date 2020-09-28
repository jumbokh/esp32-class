#include "ObloqAdafruit.h"
#include "Arduino.h"

ObloqAdafruit::ObloqAdafruit(Stream *serial, const String& ssid, const String& pwd, const String& iotId, const String& iotPwd)
{
    _serial = serial;
    _ssid   = ssid;
    _pwd    = pwd;
    _iotId  = iotId;
    _iotPwd = iotPwd;
}

void ObloqAdafruit::update()
{
    readSerial();

    // update state machine
    switch(_state)
    {
        case STATE_PING :
            if ((millis() - _time) >= PING_INTERVAL)
            {
                _time = millis();
                sendMsg("|1|1|");
            }
            break;
        case STATE_WIFI_CONNECTING:
            // connect Wifi
            if ((millis() - _time) >= WIFI_CONNECT_INTERVAL)
            {
                _time = millis();
                sendMsg("|2|1|" + _ssid + "," + _pwd + "|");
            }
            break;
        case STATE_WIFI_CONNECTED:
            pollTopicArray();
            flushPublishQueue();

            //fetching timeout
            if( _fetching && (millis() - _time  > FETCHING_TIMEOUT))
            {
                _time = millis();
                _fetching = false;
            }
            break;
    }



}
void ObloqAdafruit::readSerial(){
    // listen to serial data
    if (_serial->available())
	{
		String data = _serial->readStringUntil('\r');
		while (true)
		{
			int l = data.length();
			int i = data.indexOf('\r');
			String subData = data.substring(0, i);
			receiveData(subData);

			if (i == -1 || l - i <= 1){
                break;
            }else{
                subData = data.substring(i + 1, l);
        		data = String(subData);
            }
		}
	}
}

void ObloqAdafruit::receiveData(const String& data)
{
    String type,code, message;
    //split string
    type = strtok((char *)(data.c_str()), "|");
    code = strtok(NULL, "|");
    message = strtok(NULL, "|");

    if(type == SYSTEMTYPE){
        if(code == SYSTEMPING){
            _time = millis() - WIFI_CONNECT_INTERVAL;
            _state = STATE_WIFI_CONNECTING;
        }
    }
    else if(type == WIFITYPE){
        if(code == WIFIDISCONNECT){
            _time = millis() - WIFI_CONNECT_INTERVAL;
            _state = STATE_WIFI_CONNECTING;
        }
        else if(type == WIFITYPE){
            _state = STATE_WIFI_CONNECTED;
            _queue_in = _queue_out = 0;
            _fetching = false;
        }
    }
    else if(type == HTTPTYPE){
        httpHandle(code,message);
    }


}

void ObloqAdafruit::subscribe(String topic)
{
    // abort if too many topics are already subscribed
    if(_topicCount >= TOPICS_COUNT)
        return;

    // ignore if topic already subscribed
    for(int i = 0; i < _topicCount; i++)
        if(_topics[i].name == topic)
            return;

    // add topic to the topics array
    _topics[_topicCount++] = {topic, "", 0};

}


void ObloqAdafruit::pollTopicArray()
{
    // do not poll if a publish is pending, or if fetching already... or no topic subscribed
    if( (_queue_in != _queue_out) || _fetching || _topicCount == 0)
        return;

    if((millis() - _topics[_currentTopic].lastMillis) > POLL_INTERVAL)
    {
        String msg = "|3|1|http://io.adafruit.com/api/v2/"+_iotId+"/feeds/"+_topics[_currentTopic].name+"/data/retain?X-AIO-Key="+_iotPwd + "|";
        sendMsg(msg);
        _fetching = true;
        _topics[_currentTopic].lastMillis = millis();
    }

}



void ObloqAdafruit::flushPublishQueue()
{
    // nothing to do if pending or nothing in the queue
    if(_fetching || (_queue_in == _queue_out) )
        return;

    //skips elements if in_index advanced too much
    if(_queue_in-QUEUE_COUNT>_queue_out)
        _queue_out = _queue_in-QUEUE_COUNT;

    // |3|2|url,content|
    String msg = "|3|2|http://io.adafruit.com/api/v2/"+_iotId+"/feeds/"+_queue[_queue_out % QUEUE_COUNT].topic+"/data?X-AIO-Key="+_iotPwd + ",{\"value\":\""+_queue[_queue_out % QUEUE_COUNT].value+"\"}|";
    sendMsg(msg);

    _fetching = true;
    _time = millis();
    _queue_out++;
}

void ObloqAdafruit::publish(const String& topic, const String& value)
{
    //add the message to the message queue
    _queue[_queue_in++ % QUEUE_COUNT] =  {topic, value};
}

void ObloqAdafruit::sendMsg(const String & msg)
{
    _serial->print(msg + "\r");
}

void ObloqAdafruit::httpHandle(const String& code, const String& message){
    // a succesful post message
    // anyway many post messages dont show up
    // here because they are too long....=(
    // or some appear as an empty message with code=200 ...bizarre...
    // todo: catch errors

    // enable fetch again
    _fetching = false;
    //prevent fetching timout
    _time = millis();

    if(_msgHandle && message)
    {
        //a succesful get message in CSV format
        if(code=="200" && message.indexOf(",,,")>0){
            //discard bullshit
            message.replace(",,,", "");
            message.replace("\n", "");

            //trigger if message changed
            if(_topics[_currentTopic].lastMsg != message){
                _msgHandle(_topics[_currentTopic].name,message);
                _topics[_currentTopic].lastMsg = message;
            }
        }

        // move to next topic
        // handle one topic at a time to know which topic is responding
        _currentTopic++;
        _currentTopic %= _topicCount;
    }


}
