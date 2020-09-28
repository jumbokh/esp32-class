#ifndef _ObloqAdafruit_H_
#define _ObloqAdafruit_H_
#include "Arduino.h"

#define TOPICS_COUNT 5
#define QUEUE_COUNT 5

#define SYSTEMTYPE "1"
#define WIFITYPE   "2"
#define HTTPTYPE   "3"

#define SYSTEMPING      "1"
#define SYSTEMVERSION   "2"
#define SYSTEMHEARTBEAT "3"

#define WIFIDISCONNECT    "1"
#define WIFICONNECTING    "2"
#define WIFICONNECTED     "3"
#define WIFICONNECTFAILED "4"

#define STATE_PING 1
#define STATE_WIFI_CONNECTING 2
#define STATE_WIFI_CONNECTED 3

// when fetching, wait for response before moving to another fecth.
// the timeout is here in case of no response from previous fecth.
#define FETCHING_TIMEOUT 60000
#define PING_INTERVAL 2000
#define WIFI_CONNECT_INTERVAL 60000
#define POLL_INTERVAL 1000


typedef struct  {
    String name;
    String lastMsg;
    long lastMillis;
} Topic;

typedef struct  {
    String topic;
    String value;
} PublishQueueItem;



class ObloqAdafruit
{
public:
    typedef void (*MsgHandle)(const String& topic, const String& message);

public:
    ObloqAdafruit(Stream *serial, const String& ssid, const String& pwd, const String& iotId, const String& iotPwd);
    void setMsgHandle(MsgHandle handle) {_msgHandle = handle;};
    void update();
    void subscribe(String topic);

    void publish(const String& topic, const String& value);
    // convenience signatures
    void publish(const String& topic, int value)    {publish(topic, String(value));};
    void publish(const String& topic, long value)   {publish(topic, String(value));};
    void publish(const String& topic, double value) {publish(topic, String(value));};
    void publish(const String& topic, float value)  {publish(topic, String(value));};

private:
    Stream *_serial = NULL;
	String _ssid = "";
	String _pwd = "";
    String _iotId = "";
    String _iotPwd = "";
    PublishQueueItem _queue[QUEUE_COUNT];
    unsigned int _queue_in = 0;
    unsigned int _queue_out = 0;
    bool _fetching = false;
    bool _polling = false;
    MsgHandle _msgHandle = NULL;
    int _state = STATE_PING;
    Topic _topics[TOPICS_COUNT];
    int _topicCount = 0;
    int _currentTopic = 0;
    unsigned long _time = 0;

private:
    void httpHandle(const String& code, const String& message);
    void sendMsg(const String & msg);
    void readSerial();
    void receiveData(const String& data);
    void pollTopicArray();
    void flushPublishQueue();
};

#endif
