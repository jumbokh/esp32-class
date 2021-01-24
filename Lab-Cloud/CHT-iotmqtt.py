from machine import Pin
from time import sleep
import dht
import time
import network     
from umqtt.robust import MQTTClient # mqtt函式庫

# 連線至無線網路
LED=Pin(2,Pin.OUT,value=0)          # 連上WiFi前關閉內鍵led燈
sta=network.WLAN(network.STA_IF)
sta.active(True)   
sta.connect('jumboap','0953313123')  
while not sta.isconnected() :
    pass
LED.value(1)
print('Wifi連線成功')

# mqtt參數
mqtt_client_id = 'temperature'              # 用戶端識別名稱(可以隨意取名)
CHT_URL = 'iot.cht.com.tw'           # 主機網址
CHT_USERNAME = 'DKP4TAKYPFAK3HBHGF' # 帳戶名稱
CHT_IO_KEY = 'DKP4TAKYPFAK3HBHGF'   # 金鑰

client = MQTTClient(client_id=mqtt_client_id,  # 用戶端識別名稱
                    server=CHT_URL,            # 中介伺服器網址
                    user=CHT_USERNAME,         # 帳戶名稱
                    password=CHT_IO_KEY)       # 金鑰                      
           
client.connect()           # 連線至mqtt伺服器

sensor = dht.DHT11(Pin(5))
data=0

while True:            
  for i in range(5): 
      try:
        sleep(5)
        sensor.measure()
        temp = sensor.temperature()
        data=data+temp
        print('.',end='')
      except OSError as e:
        print('Failed to read sensor.')
    
  data=data/5                 
  print(data)
  payload=[{"id":"DHT11",           
             "value":[str(data)]}]  
        # 傳送資料到IoT平台
  client.publish(                   
         b'/iot/v1/device/25640304019/rawdata',
         str(payload).encode()    # 傳送的資料改為bytes物件
         )                 
  print("上傳完畢")
    
  data=0
  time.sleep(20)      # 暫停60秒