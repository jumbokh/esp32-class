from machine import Pin

toggle = 1 # 儲存開關狀態，預設: 高電位

led = Pin(2, Pin.OUT)    # 設定 LED 接腳為 GPIO2 且為輸出
sw = Pin(19, Pin.IN, Pin.PULL_UP)      # 設定 按鈕 接腳為 GPIO0 且為輸入
print(sw.value())

while True:
    if sw.value() == 0:    # 如果開關被按下
        toggle = not toggle # 取開關狀態變數為反向值
        led.value(toggle)   # 設定 LED 狀態
        while sw.value() == 1: # 若開關一直被按著
            pass               # 什麼事都不做