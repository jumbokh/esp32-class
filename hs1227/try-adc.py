from machine import ADC,Pin
import time

adc = ADC(Pin(32))          # 在ADC引腳上創建ADC物件
adc.read()                  # 讀取測量值, 0-4095 表示電壓從 0.0v - 1.0v

adc.atten(ADC.ATTN_11DB)    # 設置 11dB 衰減輸入 (測量電壓大致從 0.0v - 3.6v)
adc.width(ADC.WIDTH_9BIT)   # 設置 9位 精度輸出 (返回值 0-511)
while True:
 print(adc.read())           # 獲取重新配置後的測量值
 time.sleep(2)