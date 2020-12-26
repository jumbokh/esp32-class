from machine import DAC
from machine import Pin
import utime, math


dac = DAC(Pin(26,Pin.OUT), bits=8)

def pulse(dac, period, gears):
    """呼吸燈函數

    Arguments:
        dac {[DAC]} -- [DAC物件]
        period {[type]} -- [週期 ms]
        gears {[type]} -- [亮度檔位]
    """

    for i in range(2 * gears):
        val = int((math.sin(i / gears * math.pi) * 12) + 2000)
        dac.write(val%128)
        # 延時
        utime.sleep_ms(int(period / (2 * gears)))

# 呼吸十次
for i in range(10):
    pulse(dac, 2000, 100)
