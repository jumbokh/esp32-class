from machine import Pin
from time import sleep
import dht
import time
import network     
from umqttsimple import MQTTClient
import ubinascii

ssid = 'jumboap'
password = '0953313123'
mqtt_server = 'gpssensor.ddns.net'
#EXAMPLE IP ADDRESS
#mqtt_server = '192.168.1.144'
client_id = ubinascii.hexlify(machine.unique_id())
topic_pub = b'/iotclass/T'
topic_pub1 = b'/iotclass/H'
topic_sub = b'/iotclass/lamp'
topic_sub1 = b'/iotclass/TH'

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
# ------------------------------------------------
p5=Pin(5, Pin.IN)
d=dht.DHT11(p5)        #建立 DHT11 物件
p2 = Pin(2, Pin.OUT)

def sub_cb(topic, msg):
  print((topic, msg))
  
  if topic == topic_sub1:
    T, H = read_TH()
    client.publish(topic_pub, str(T))
    client.publish(topic_pub1, str(H))
    print('ESP received read TH')
  elif topic == topic_sub and msg == b'ON':
    p2.value(1)
    print('ESP received Lamp ON')
  elif topic == topic_sub and msg == b'OFF':
    p2.value(0)
    print('ESP received Lamp OFF')
  
  

def connect_and_subscribe():
  global client_id, mqtt_server, topic_sub
  client = MQTTClient(client_id, mqtt_server)
  client.set_callback(sub_cb)
  client.connect()
  client.subscribe(topic_sub)
  client.subscribe(topic_sub1)
  print('Connected to %s MQTT broker, subscribed to %s topic' % (mqtt_server, topic_sub))
  return client

def restart_and_reconnect():
  print('Failed to connect to MQTT broker. Reconnecting...')
  time.sleep(10)
  machine.reset()
  
def read_TH():
  print('Measuring....')
  d.measure()                  #重新測量溫溼度
  time.sleep(0.5)
  t=d.temperature()        #讀取攝氏溫度
  h=d.humidity()             #讀取相對溼度
  print('Temperature=', t, 'C', 'Humidity=', h, '%')
  return t,h

try:
  client = connect_and_subscribe()
except OSError as e:
  restart_and_reconnect()

p5=Pin(5, Pin.IN)
d=dht.DHT11(p5)        #建立 DHT11 物件

while True:
  try:
    client.check_msg()
    if (time.time() - last_message) > message_interval:
      T, H = read_TH()
      client.publish(topic_pub, str(T))
      client.publish(topic_pub1, str(H))
      last_message = time.time()
  except OSError as e:
    restart_and_reconnect()