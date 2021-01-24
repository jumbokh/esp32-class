from machine import Pin
from time import sleep
import dht
import time
from keras_lite import Model  
import ulab as np
import network     # 匯入network模組
import urequests   # 匯入urequests模組

# 連線至無線網路
sta=network.WLAN(network.STA_IF)
sta.active(True)   
sta.connect('jumboap','0953313123') 

while not sta.isconnected() :
    pass

print('Wifi連線成功')

device_id = "25640304019"
headers={"CK":"DKP4TAKYPFAK3HBHGF"} 

# 中華電信IoT平台
url_CHT="http://iot.cht.com.tw/iot/v1/device/" \
        +device_id+"/rawdata"

sensor = dht.DHT11(Pin(5))

data=0

while True:            
  for i in range(5): 
      try:
        sleep(0.5)
        sensor.measure()
        temp = sensor.temperature()
        data=data+temp
        print('.',end='')
      except OSError as e:
        print('Failed to read sensor.')
    
  data=data/5                 
  print(data)
  CHT_data=[{"id":"25640304019",           
             "value":[str(data)]}]  
    
  urequests.post(url_CHT,json=CHT_data,   # 上傳資料至IoT平台
                   headers=headers)  
    
  print("上傳完畢")
    
  data=0
  time.sleep(60)      # 暫停60秒