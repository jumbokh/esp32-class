from machine import ADC,Pin, PWM
from time import sleep

adc = ADC(Pin(32))          # 在ADC引腳上創建ADC物件
adc.read()                  # 讀取測量值, 0-4095 表示電壓從 0.0v - 1.0v
frequency = 5000
led = PWM(Pin(2), frequency)

adc.atten(ADC.ATTN_11DB)    # 設置 11dB 衰減輸入 (測量電壓大致從 0.0v - 3.6v)
adc.width(ADC.WIDTH_9BIT)   # 設置 9位 精度輸出 (返回值 0-511)
duty_cyle = 0
while True:
 duty_cyle = adc.read()
 print(duty_cyle)           # 獲取重新配置後的測量值
 led.duty(duty_cyle)
 sleep(0.005)