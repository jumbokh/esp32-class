import time

time.sleep(1)           # sleep for 1 second
time.sleep_ms(500)      # sleep for 500 milliseconds
time.sleep_us(10)       # sleep for 10 microseconds
start = time.ticks_ms() # get millisecond counter
for i in range(1000):
    time.sleep_ms(1)
delta = time.ticks_diff(time.ticks_ms(), start) # compute time difference
print(start)
print(delta)