from machine import Pin

led = Pin(2, Pin.OUT)    # 設定 LED 接腳為 GPIO2 且為輸出
sw = Pin(19, Pin.IN, Pin.PULL_UP)      # 設定 按鈕 接腳為 GPIO0 且為輸入

while True:
    val = sw.value()     # 讀取按鈕狀態
    print(val)
    led.value(val)