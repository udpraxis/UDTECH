__author__ = 'darwin'


import serial
import time

loop = True
arduino = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)

time.sleep(2)

print("Initialization complete")
command = b'CM:-0.19,-1.00,-0.19\n'
command1 = b'MC:+045,+025,+140\n'

while loop:

    arduino.write(command1)
    time.sleep(0.2)
