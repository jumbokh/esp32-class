from machine import Pin
import dht
import time

d = dht.DHT11(Pin(2))

while True:
    d.measure()
    temp = d.temperature()
    hum = d.humidity()
    print('Humidity: {}%'.format(hum))
	print('Temperature: {}{}C'.format(temp, '\u00b0'))
	time.sleep(5)