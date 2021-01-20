from machine import Pin,ADC
import time
from keras_lite import Model  
import ulab as np
import network     # 匯入network模組
import urequests   # 匯入urequests模組

# 連線至無線網路
sta=network.WLAN(network.STA_IF)
sta.active(True)   
sta.connect('無線網路名稱','無線網路密碼') 

while not sta.isconnected() :
    pass

print('Wifi連線成功')

device_id = "請填入中華電信設備編號"
headers={"CK":"請填入中華電信設備金鑰"} 

# 中華電信IoT平台
url_CHT="http://iot.cht.com.tw/iot/v1/device/" \
        +device_id+"/rawdata"

mean=170.98275862068965
std=90.31162360353873     
model = Model('temperature_model.json')

adc_pin = Pin(36)        
adc = ADC(adc_pin)       
adc.width(ADC.WIDTH_9BIT)
adc.atten(ADC.ATTN_11DB) 

data=0

while True:            

    for i in range(20):              
        thermal=adc.read()     
        data=data+thermal      
        time.sleep(0.01)
    
    data=data/20         
    
    data = np.array([int(data)])        
    data = data-mean                    
    data = data/std                     
    tem = model.predict(data)  
    tem = round(tem[0]*100,1)           
    print(tem,end='   ')                      
    
    CHT_data=[{"id":"請填入中華電信感測器編號",           
               "value":[str(tem)]}]  
    
    urequests.post(url_CHT,json=CHT_data,   # 上傳資料至IoT平台
                   headers=headers)  
    
    print("上傳完畢")
    
    data=0
    time.sleep(60)      # 暫停60秒