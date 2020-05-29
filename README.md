"# esp32-class" 
### ESP32 firmware 
#### [韌體安裝](http://pizgchen.blogspot.com/2019/08/esp32-arduino-ide-esp32.html)
#### https://dl.espressif.com/dl/package_esp8266_index.json,https://dl.espressif.com/dl/package_esp32_index.json
##
#### Erase flash
* python -m esptool erase_flash
##
<pre>
D:\esp32\esp32-class>python -m esptool erase_flash
esptool.py v2.8
Found 1 serial ports
Serial port COM4
Connecting........__
Detecting chip type... ESP32
Chip is ESP32D0WDQ6 (revision 1)
Features: WiFi, BT, Dual Core, Coding Scheme None
Crystal is 40MHz
MAC: 30:ae:a4:28:20:10
Uploading stub...
Running stub...
Stub running...
Erasing flash (this may take a while)...
Chip erase completed successfully in 4.0s
Hard resetting via RTS pin...
</pre>
