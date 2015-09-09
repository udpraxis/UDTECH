__author__ = 'darwin'


import serial
import numpy
import matplotlib.pyplot as plt
from drawnow import *

ardunioData = serial.Serial('/dev/ttyACM0', 9600)

while True :
    while(ardunioData.inWaiting()== 0):
        pass
    arduinoString = ardunioData.readline()
    dataArray = arduinoString.split(',')
    humidity = float(dataArray[0])
    temperature = float(dataArray[1])
    hic = float(dataArray[2])

    print(humidity)