### ESP32 IO
## 2020/12/27 ESP32 LAB
### 材料清單:
* ESP32S * 1
* Micro USB 通訊線 * 1
* LED 燈
* 按鈕
* Half+ 麵包板 * 1
* 杜邦線 少許
##
### ![ESP32](https://github.com/jumbokh/esp32-class/blob/master/images/ESP32s-pinout.png)
##
### Lab 1 read button state
* ![readin](https://github.com/jumbokh/esp32-class/blob/master/images/ESP32-button-sw_bb.jpg)
* [read gpio in](https://github.com/jumbokh/esp32-class/blob/master/hs1227/readin.py)
* [toggle](https://github.com/jumbokh/esp32-class/blob/master/hs1227/toggle.py)
* [bumping](https://github.com/jumbokh/esp32-class/blob/master/hs1227/bump.py)
* ![bumping](https://github.com/jumbokh/esp32-class/blob/master/images/bumping.png)
* [switch](https://github.com/jumbokh/esp32-class/blob/master/hs1227/switch-led.py)
* ![dip](https://github.com/jumbokh/esp32-class/blob/master/images/dip.png)
##
### Lab 2 ADC
* [try ADC](https://github.com/jumbokh/esp32-class/blob/master/hs1227/try-adc.py)
##
### Lab 3 PWM
* [PWM](https://github.com/jumbokh/esp32-class/blob/master/hs1227/pwm-led.py)
##
### Lab 4 Build DHT Web Service
* Create ap.txt
<pre>
my-ssid
my-key
</pre>
##
* create main.py
<pre>
# -*- coding: utf-8 -*-

import machine
import network
import time
import os

#- check ap config file
AP_SSID = 'upy'
AP_PWD = 'pypypypy'
ap_config = None
ap_config_fn = 'ap.txt'
if ap_config_fn in os.listdir():
    print('ap config here!')
    f = open(ap_config_fn)
    ap_config = f.read()
    f.close()
if ap_config:
    print( ('ap_config:', ap_config))
    ap_config = ap_config.split('\n')
    AP_SSID = ap_config[0].strip()
    AP_PWD = ap_config[1].strip()
print('line to: ', (AP_SSID, AP_PWD))

#-- 連到AP 為Station
sta_if = network.WLAN(network.STA_IF)
sta_if.active(True)
sta_if.connect(AP_SSID, AP_PWD)
sta_if.isconnected()
for i in range(20):
    time.sleep(0.5)
    if sta_if.isconnected():
        break
sta_ip = ''
if sta_if.isconnected():
    print('connected!  --> ', sta_if.ifconfig())
    sta_ip = sta_if.ifconfig()[0]
else:
    print('not connected!  --> ', sta_if.ifconfig())


import socket
from machine import Pin
from machine import PWM
import dht
#from hcsr04 import HCSR04


#Setup PINS
led = machine.Pin(2, machine.Pin.OUT)


# th_sensor
th_sensor = dht.DHT11(Pin(5))


#Setup Socket WebServer
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('0.0.0.0', 80))
s.listen(5)
while True:
    conn, addr = s.accept()
    print("Got a connection from %s" % str(addr))
    request = conn.recv(1024)
    print("Content = %s" % str(request))

    request = str(request)
    led_on = request.find('GET /?LED=ON')
    led_off = request.find('GET /?LED=OFF')
    th_sensor_read = request.find('GET /?th_sensor=read')


    if led_on >= 0:
        print('TURN Led ON')
        led.value(0)
    if led_off >= 0:
        print('TURN Led OFF')
        led.value(1)
   

    my_t = None
    my_h = None
    if th_sensor_read >= 0:
        print('th_sensor read')
        th_sensor.measure()    
        my_t = th_sensor.temperature()  
        my_h = th_sensor.humidity()
        print('T=', th_sensor.temperature())
        print('H=', th_sensor.humidity())

    f = open('webtool.html')

    while(1):
        html = f.read(1024)

        if my_t:
            html = html.replace('T=?', 'T={}{}C'.format(my_t,'\u00b0'))
        else:
            html = html.replace('T=?', '')
        if my_h:
            html = html.replace('H=?', 'H={}{}'.format(my_h,'%'))
        else:
            html = html.replace('H=?', '')
        #conn.send(html)
        conn.sendall(html) #改用send all就不會有資料傳一半的問題
        if(len(html)<=0):
            break
    f.close()
    conn.close()
</pre>
##
* create webtool.html
<pre>

<!DOCTYPE html>
<html>
<head> <title>upy webserver</title> </head>
<center><h2>upy webserver</h2></center>
<h3>
webREPL: <a href="http://micropython.org/webrepl/" target="_blank">webrepl</a>
<br>
Doc: <a href="https://docs.micropython.org/en/latest/esp8266/esp8266/quickref.html" target="_blank">Quick reference</a>
</h3>
<hr>

<form>
<b>LED (D4):</b><br>
<button name="LED" value="ON" type="submit">ON</button><br>
<button name="LED" value="OFF" type="submit">OFF</button><br>
</form>

<form>
<b>T/H sensor (D1):</b><br>
<button name="th_sensor" value="read" type="submit">Read</button><br>
T=?degree
H=?unit
</form>

</html>
</pre>
##
