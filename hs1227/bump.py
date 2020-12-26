# 解決彈跳問題
import time
from machine import Pin

led = Pin(2, Pin.OUT)    # 設定 LED 接腳為 GPIO2 且為輸出
sw = Pin(19, Pin.IN, Pin.PULL_UP)      # 設定 按鈕 接腳為 GPIO0 且為輸入

while True:
    if sw.value() == 0:    # 如果開關被按下
        time.sleep_ms(20)   # 先暫停 20ms
        led.value(not led.value())   # 設定 LED 狀態
        while sw.value() == 0: # 若開關一直被按著
            pass               # 什麼事都不做