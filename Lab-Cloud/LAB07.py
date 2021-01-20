from machine import Pin,ADC
import time
from keras_lite import Model  
import ulab as np
import network     # 匯入network模組
import urequests   # 匯入urequests模組

# 連線至無線網路
sta=network.WLAN(network.STA_IF)
sta.active(True)   
sta.connect('無線網路名稱','無線網路密碼')  # 更換為無線網路帳號、密碼 

while not sta.isconnected() :
    pass

print('Wifi連線成功')

device_id = "請填入您的中華電信設備編號"
headers={"CK":"請填入中華電信平台金鑰"} 

# 中華電信IoT平台
url_CHT="http://iot.cht.com.tw/iot/v1/device/"+device_id+"/rawdata"

# LINE(請記得更改為http)
url_line="請填入IFTTT複製的網址(請記得將https更改為http)"

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
    
    CHT_data=[{"id":"請填入中華電信感測器編號","value":[str(tem)]}]
    
    urequests.post(url_CHT,json=CHT_data,headers=headers)  
    
    print("上傳完畢")
    
    if(tem>=37.5):   # 當體溫超過37.5度時, 傳LINE做警告
        urequests.get(url_line+"?value1="+str(tem)) # 傳送至LINE
        print("警告!!!發燒了!!!")
    
    data=0
    time.sleep(60)      