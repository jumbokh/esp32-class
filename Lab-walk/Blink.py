from machine import Pin
import time

p0 = Pin(2, Pin.OUT)    # create output pin on GPIO2
for i in range(5):
    p0.on()                 # set pin to "on" (high) level
    time.sleep(1)
    p0.off()                # set pin to "off" (low) level
    time.sleep(1)
p0.value(0)             # set pin to on/high