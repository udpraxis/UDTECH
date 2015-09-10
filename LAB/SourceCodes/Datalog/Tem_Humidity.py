__author__ = 'darwin'


import serial
import numpy
import matplotlib.pyplot as plt
from drawnow import *
import time

#Object creation
temp_array = []
humidity_array = []
heatIndex_array = []
cont = 0
min10_Count = 0
datalog_count = 0


ardunioData = serial.Serial('/dev/ttyACM0', 9600)

#interactive mode = true by this code
plt.ion()


#Create funtion that make graph
def makeFig():
    plt.plot(temp_array, 'r-')
    plt.grid()
    plt.xlabel("Time")
    plt.ylabel("Celcius")


#Funktion Window
def windowStatus(init, angular):
    pass
#Funktion for heater
def heaterStatus(param):
    pass

#main program
while True :
    while(ardunioData.inWaiting()== 0):
        pass

    #Read the line from arduino and change into string
    arduinoString = str(ardunioData.readline().decode('utf-8'))
    data = arduinoString.split(',')

    #String to float conversion
    single_humidity = float(data[0])
    single_temperature = float(data[1])
    heatIndex = float(data[2])

    #Store float data into array
    temp_array.append(single_temperature)
    humidity_array.append(single_humidity)
    heatIndex_array.append(heatIndex)

    #Call Drawnow to update the live graph
    drawnow(makeFig)
    plt.pause(0.0001)
    cont = cont +1
    min10_Count = min10_Count +1

    if (min10_Count >= 10):
        datalog_count = datalog_count + 1
        plt.savefig('DataLOG/10 Mins Datas (%d).pdf' % datalog_count)
        min10_Count = 0
        temp_array.clear()





