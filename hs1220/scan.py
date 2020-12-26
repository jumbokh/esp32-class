import network
import time

sta = network.WLAN(network.STA_IF)
while True:
    state = sta.active(True)
    if state == True:
        break;
    time.sleep(0.5)
nets = sta.scan()
print('SSID','\t\t\t\t','Channel','\t\t\t','dbm')
for net in nets:
    #print(net)
    ssid = net[0].decode('ascii')
    channel = net[2]
    dbm = net[3]
    print(ssid,'\t\t\t\t',channel,'\t\t\t',dbm)
    