from machine import I2C, Pin
import mpu6050
import time
from keras_lite import Model   # 匯入第三方函式庫
import ulab as np      

#增加神經網路的參數
mean = 849.1830065359477         # 請複製Colab上的mean
std = 16766.660464036682         # 請複製Colab上的std
model = Model('walk_model.json') # 建立模型物件
label_name = ['others','walk']   # label名稱。要與Colab指定的順序一樣
   
i2c = I2C(scl=Pin(22),sda=Pin(21))
accelerometer = mpu6050.accel(i2c)
data=[]             
reset=False         

while(accelerometer.get_values()['AcX']==0 and
      accelerometer.get_values()['AcY']==0 and
      accelerometer.get_values()['AcZ']==0):  
    pass

step_count=0           # 總步數
last_time=time.time()  # 記錄上次時間

while True:
    
    if(reset==False):
        time.sleep(0.3)
        data=[]
        accelerometer = mpu6050.accel(i2c)   
        six_data = accelerometer.get_values()
        print('start:')
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
            time.sleep(0.01)                        # 暫停 0.01 秒        
        data = np.array([data])                     # 將data轉換為numpy格式
        data = data-mean                            # data減掉平均數
        data = data/std                             # data除以標準差
        status_label = model.predict_classes(data)  # 得出狀態(0 或 1)
        status = label_name[status_label[0]]        # 轉換為label(others 或 walk)
        
        print('status:',status)
        print('')
        
        if(status=='walk'):
            step_count += 1     # 步數加 1
   
    last_AcX=AcX

    time.sleep(0.01)   
    
    if(time.time()-last_time>=60):    # 每1分鐘顯示1次  
        print("總步數:",step_count)    # 顯示步數
        print('')
        step_count=0                  # 重置步數
        last_time=time.time()         # 重置時間
