from machine import Pin

toggle = 1 # 儲存開關狀態，預設: 高電位

led = Pin(2, Pin.OUT)    # 設定 LED 接腳為 GPIO2 且為輸出
sw = Pin(19, Pin.IN, Pin.PULL_UP)      # 設定 按鈕 接腳為 GPIO0 且為輸入
if sw.value() == 1:
   print('HIGH')
   led.value(1)
else:
   print('{}:'.format(sw.value()),'LOW')
   led.value(0)
   