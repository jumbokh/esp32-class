from machine import Pin,ADC,PWM        
import time

led=Pin(25,Pin.OUT,value=0)             # LED燈腳位
horn=PWM(Pin(14),duty=0,freq=2000)      # 喇叭腳位
button_yes=Pin(12,Pin.IN,Pin.PULL_UP)   # 儲存按鈕
button_no=Pin(13,Pin.IN,Pin.PULL_UP)    # 捨棄按鈕

adc = ADC(Pin(36))       # 設定36為ADC腳位
adc.width(ADC.WIDTH_12BIT) 
adc.atten(ADC.ATTN_11DB) 

f = open('on.txt','w')   # 檔案名稱

for i in range(100):     # 100筆資料
    time.sleep(0.1)
    if(i>=100/2):        # 紀錄次數過半時, 開啟燈
        led.value(1)
    
    print('')
    print('第'+str(i+1)+'筆')
    while True:
        sound=adc.read()   # 接收聲音
        if(sound>100):     # 有聲音時
            print('')
            print('action')
            no_sound=0     # 重置沒聲音次數
            data=[sound]   # 重置data
            
            # 沒聲音次數少於150或超過資料儲存量時
            while(no_sound<150 and len(data)<550): 
                sound=adc.read()  # 接收到的聲音
                data.append(sound)
                if(sound==0):     # 沒聲音時
                    no_sound+=1   # 沒聲音次數+1
                else:             # 有聲音時
                    no_sound=0    # 重置聲音次數
                time.sleep_us(500)                    
            data=data[:-150]      # 將0的部分刪除
            
            if(len(data)<150):    # 如果資料長度小於150, 認為是噪音
                print('noise, try again')
                continue
            # 播放音效
            for j in data:
                horn.duty(int(j/4))      
                time.sleep_us(500)
                
            print(len(data))      # 顯示資料長度
            
            while(len(data)<400): # 如果資料長度不夠
                data.append(0)    # 補充數字0

            horn.duty(0)          # 關閉聲音
            
            print('Save or Delete?',end=' ')
            
            while(button_yes.value()==1 and
                  button_no.value()==1):    
                time.sleep(0.01)
                
            if(button_yes.value()==0):
                f.write(str(data)[1:-1])  # data存到檔案中
                f.write("\n")             # 換行字元
                print('Save')
                break             # 跳脫while迴圈
            
            elif(button_no.value()==0):
                print('Delete')
                time.sleep(0.1)   # 避免出現雜訊
                print('try again')
            
        time.sleep_us(500)        # sleep_us=1微秒=0.000001秒       
led.value(0)  # 關燈
f.close()