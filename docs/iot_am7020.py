#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# iot_project.py
# @Author : Zack Huang ()
# @Link   : zack@atticedu.com
# @Date   : 2020/11/11 下午1:39:34

from time import time, sleep
from sim7020.sim7020_nb import SIM7020NB
from sim7020.sim7020_mqtt import SIM7020MQTT
from tsl2561 import TSL2561


tsl = TSL2561(debug=True)

apn = "twm.nbiot"
band = 28
MQTT_BROKER = "io.adafruit.com"
PORT = 1883
MQTT_USERNAME = "Zack_Huang"
MQTT_PASSWORD = "XXXXXXXXXXXXXXXXXXXX"

# topics
LUX = "Zack_Huang/feeds/pi3.lux"
UPLOAD_INTERVAL = 60


nb = SIM7020NB("/dev/ttyS0", 115200, 18)
mqtt = SIM7020MQTT(nb)


def nbConnect():
    print("Initializing modem...")
    while((not nb.init() or (not nb.nbiotConnect(apn, band)))):
        print(".")

    print("Waiting for network...")
    while(not nb.waitForNetwork()):
        print(".")
        sleep(5)
    print("success")


def reConnBroker():
    if(not mqtt.chkConnBroker()):
        print("Connecting to", MQTT_BROKER, "...")
        if(mqtt.connBroker(MQTT_BROKER, PORT, username=MQTT_USERNAME, password=MQTT_PASSWORD, mqtt_id="MY_AM7020_TEST_MQTTID")):
            print("success")
        else:
            print("fail")


def pubAdafruitIO(topic, msg):
    print("publish {} to {}".format(msg, topic))
    if(mqtt.publish(topic, msg)):
        print("success")
    else:
        print("Fail")


def main():
    nbConnect()
    reConnBroker()
    chk_net_timer = 0
    pub_data_timer = 0
    get_lux_timer = 0

    lux = 0
    while(True):
        if(time() > get_lux_timer):
            get_lux_timer = time() + 5
            lux = tsl.lux()
        if(time() > chk_net_timer):
            chk_net_timer = time() + 10
            if(not nb.chkNet()):
                nbConnect()
            reConnBroker()

        if(time() > pub_data_timer):
            pub_data_timer = time() + UPLOAD_INTERVAL
            pubAdafruitIO(LUX, lux)
        mqtt.procSubs()


main()
