from machine import I2C, Pin
import mpu6050

i2c = I2C(scl=Pin(22),sda=Pin(21))
accelerometer = mpu6050.accel(i2c)

while(accelerometer.get_values()['AcX']==0 and
      accelerometer.get_values()['AcY']==0 and
      accelerometer.get_values()['AcZ']==0 ):
    pass

six_data = accelerometer.get_values()

print(six_data)
print(six_data['AcX'])