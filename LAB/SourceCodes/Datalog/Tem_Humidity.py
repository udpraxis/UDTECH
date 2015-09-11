__author__ = 'darwin'


import serial
import numpy
import matplotlib.pyplot as plt
from drawnow import *
import time
import sys
import csv


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
    try:
        arduinoString = str(ardunioData.readline().decode('utf-8'))
        data = arduinoString.split(',')
    except:
        print("DataError!")

    #String to float conversion
    try:
         single_humidity = float(data[0])
    except:
        print("DataError in Humidity")
    try:
        single_temperature = float(data[1])
    except:
        print("DataError in Temperature")
    try:
        heatIndex = float(data[2])
    except:
        print("DataError in HeatIndex")

    #Store float data into array
    temp_array.append(single_temperature)
    humidity_array.append(single_humidity)
    heatIndex_array.append(heatIndex)

    #Call Drawnow to update the live graph
    drawnow(makeFig)
    plt.pause(0.0001)

    with open("Data/Excels/Data.csv", "a")as log:
            logWriter = csv.writer(log)
            logWriter.writerow([single_temperature, single_humidity, heatIndex])


    min10_Count = min10_Count + 1

    if (min10_Count >= 600):
        datalog_count = datalog_count + 1
        plt.savefig('Data/Graphs/10MinsDatas(%d).pdf' % datalog_count)

        min10_Count = 0
        temp_array.clear()

    log.close()





