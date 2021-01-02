from machine import I2C, Pin
import mpu6050
import time
from keras_lite import Model
import ulab as np
import network     
from umqtt.robust import MQTTClient # mqtt函式庫

# 連線至無線網路
LED=Pin(2,Pin.OUT,value=0)          # 連上WiFi前關閉內鍵led燈
sta=network.WLAN(network.STA_IF)
sta.active(True)   
sta.connect('your-ssid','your-key')  
while not sta.isconnected() :
    pass
LED.value(1)                        # 連上WiFi時亮燈

# mqtt參數
mqtt_client_id = 'step'              # 用戶端識別名稱(可以隨意取名)
CHT_URL = 'iot.cht.com.tw'           # 主機網址
CHT_USERNAME = '設備金鑰' # 帳戶名稱
CHT_IO_KEY = '設備金鑰'   # 金鑰

client = MQTTClient(client_id=mqtt_client_id,  # 用戶端識別名稱
                    server=CHT_URL,            # 中介伺服器網址
                    user=CHT_USERNAME,         # 帳戶名稱
                    password=CHT_IO_KEY)       # 金鑰                      
           
client.connect()           # 連線至mqtt伺服器

#增加神經網路的參數
mean = 849.1830065359477   # 請複製Colab上的mean
std = 16766.660464036682   # 請複製Colab上的std
model = Model('walk_model.json') 
label_name = ['others','walk']  
  
i2c = I2C(scl=Pin(22),sda=Pin(21))
accelerometer = mpu6050.accel(i2c) 
data=[]             
reset=False

while(accelerometer.get_values()['AcX']==0 and
      accelerometer.get_values()['AcY']==0 and
      accelerometer.get_values()['AcZ']==0):  
    pass

step_count=0       # 總步數
last_time=time.time()  # 記錄上次時間

while True:
    
    if(reset==False):
        time.sleep(0.3)
        data=[]
        accelerometer = mpu6050.accel(i2c)   
        six_data = accelerometer.get_values()
        print('start:',end='')
        last_AcX=six_data['AcX']          
        reset=True
        
    
    six_data = accelerometer.get_values()   
    AcX=six_data['AcX']    

    
    if(abs(AcX-last_AcX)>3000):
        
        reset=False  # 重置reset
        
        for i in range(17):
            six_data = accelerometer.get_values()   

            data.append(six_data['AcX'])    
            data.append(six_data['AcY'])    
            data.append(six_data['AcZ'])    
            data.append(six_data['GyX'])    
            data.append(six_data['GyY'])    
            data.append(six_data['GyZ'])    
            time.sleep(0.01)
        data = np.array([data])      # 將data轉換為numpy格式
        data = data-mean             # data減掉平均數
        data = data/std              # data除以標準差
        status_label = model.predict_classes(data)   # 得出狀態
        status = label_name[status_label[0]]
        
        print(status)
        print('')
        
        if(status=='walk'):
            step_count += 1          # 總步數加 1

    last_AcX=AcX

    time.sleep(0.01)   
    
    if(time.time()-last_time>=60):   # 每1分鐘顯示1次  
        print("總步數:",step_count)   # 顯示步數
        
        payload=[{"id":"step","value":[step_count]}] # 傳送的資料
        # 傳送資料到IoT平台
        client.publish(                   
                   b'/iot/v1/device/25611797139/rawdata',
                   str(payload).encode()    # 傳送的資料改為bytes物件
                   )               
        print('publish finish')
        step_count=0               # 重置步數
        last_time=time.time()      # 重置時間
