from machine import PWM,Pin
import math

led_pwm = PWM(Pin(26),5000)

n = 100   
# 创建一个缓冲数组，用于存放一个sin波形
buf = bytearray(n)
for i in range(n):
    buf = 128 + int(127 * math.sin(2*math.pi * i/n))
    led_pwm.duty(buf)





