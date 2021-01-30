from machine import Pin,ADC
import time

adc = ADC(Pin(36))

adc.width(ADC.WIDTH_12BIT)  # 設定ADC解析度
adc.atten(ADC.ATTN_11DB)    # 設定最大電壓為3.6V

while True:
    print(adc.read())
    time.sleep(0.05)