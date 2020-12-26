import esp32
T = esp32.raw_temperature() # read the internal temperature of the MCU, in Farenheit
print(T)