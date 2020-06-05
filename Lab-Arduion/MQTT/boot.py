# Complete project details at https://RandomNerdTutorials.com

import time
from umqttsimple import MQTTClient
import ubinascii
import machine
import micropython
import network
import esp
esp.osdebug(None)
import gc
gc.collect()

ssid = 'informatics'
password = '0953313123'
mqtt_server = 'gpssensor.ddns.net'
#EXAMPLE IP ADDRESS
#mqtt_server = '192.168.1.144'
client_id = ubinascii.hexlify(machine.unique_id())
topic_sub = b'/CSU/RT'
topic_pub = b'/CSU/T'
topic_sub1 = b'/CSU/RH'
topic_pub1 = b'/CSU/H'
topic_sub2 = b'/CSU/lamp'

last_message = 0
message_interval = 5
counter = 0

station = network.WLAN(network.STA_IF)

station.active(True)
station.connect(ssid, password)

while station.isconnected() == False:
  pass

print('Connection successful')
print(station.ifconfig())
