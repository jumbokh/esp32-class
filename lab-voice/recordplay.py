from machine import Pin,ADC,PWM
import time

horn=PWM(Pin(14),duty=0,freq=6000)      # 喇叭腳位
button_yes=Pin(12,Pin.IN,Pin.PULL_UP)   # 開始按鈕

adc = ADC(Pin(36))             # 設定36為ADC腳位
adc.width(ADC.WIDTH_12BIT) 
adc.atten(ADC.ATTN_11DB) 

while True:
    if button_yes.value()==0:  # 當按下按鈕

        data=[]
        print('action')

        # 蒐集聲音
        while button_yes.value()==0 and len(data)<=1200:
            data.append(adc.read())
            time.sleep_us(167)
        
        # 播放音效
        for j in data:
            horn.duty(int(j/4))      
            time.sleep_us(167)
        horn.duty(0)           # 關閉喇叭聲音
        
    time.sleep(0.01)