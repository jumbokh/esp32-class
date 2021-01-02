from machine import I2C, Pin
import mpu6050
import time

button_yes=Pin(10,Pin.IN,Pin.PULL_UP)   # 儲存按鈕
button_no=Pin(9,Pin.IN,Pin.PULL_UP)    # 捨棄按鈕
i2c = I2C(scl=Pin(22),sda=Pin(21))
accelerometer = mpu6050.accel(i2c)
f=open('walk.txt','w')                  # 開啟txt檔

data=[]             # 儲存資料的list
reset=False         # 是否開始偵測新的一筆資料

# 等待值恢復正常
while(accelerometer.get_values()['AcX']==0 and
      accelerometer.get_values()['AcY']==0 and
      accelerometer.get_values()['AcZ']==0):  
    pass

# 儲存100筆
for j in range(100):
    
    while True:
        # 如果第一筆或上一筆資料剛結束時, 初始化六軸的值
        if(reset==False):
            time.sleep(0.3)   # 暫停一下
            print('')         
            print("第"+str(j+1)+"筆, 可以開始走動:")
            data=[]
            accelerometer = mpu6050.accel(i2c)   
            six_data = accelerometer.get_values()
            
            # 將x軸加速度的值存到『上次x軸加速度』
            last_AcX=six_data['AcX']          
            reset=True
            
        # 開始偵測值
        six_data = accelerometer.get_values()   
        AcX=six_data['AcX']    # x軸加速度

        # 上次x軸加速度與這次x軸加速度相差大於3000(數字可自行更改)
        if abs(AcX-last_AcX)>3000:
            
            reset=False
            print('action')
            
            for i in range(17):   # 收集17次6軸數值
                six_data = accelerometer.get_values()   

                data.append(six_data['AcX'])  # 加速度計 x 軸
                data.append(six_data['AcY'])  # 加速度計 y 軸
                data.append(six_data['AcZ'])  # 加速度計 z 軸
                data.append(six_data['GyX'])  # 陀螺儀 x 軸
                data.append(six_data['GyY'])  # 陀螺儀 y 軸
                data.append(six_data['GyZ'])  # 陀螺儀 z 軸
                time.sleep(0.01)              # 暫停 0.01 秒
            print('Save or Delete?',end=' ')
            # 2顆按鈕皆沒按
            while(button_yes.value()==1 and
                  button_no.value()==1):    
                time.sleep(0.01)
                
            if button_yes.value()==0:
                f.write(str(data)[1:-1])  # data存到檔案中
                f.write("\n")             # 換行字元
                print('Save')
                break                     # 跳脫while迴圈
                
            elif button_no.value()==0:
                print('Delete')                
                            
        # 將『這次的值』存到『前一次值』
        last_AcX=AcX
 
        time.sleep(0.01)   # 每次資料間隔0.01秒
    
f.close()                  # 關閉txt檔
