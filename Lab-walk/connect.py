import network
import time
import ubinascii

SSID='Tenda_5295A0'
KEY='0953313123'
sta = network.WLAN(network.STA_IF)
print(sta.active(True))
print(sta.active())
sta.connect(SSID,KEY)
mac = ubinascii.hexlify(sta.config('mac'),':').decode()
print(mac)
print(sta.ifconfig())
print(sta.isconnected())
for i in range(20):
    time.sleep(0.5)
    if sta.isconnected():
        break
print(sta.ifconfig())