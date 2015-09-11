__author__ = 'darwin'

import serial
#import numpy
import matplotlib.pyplot as plt
from matplotlib.pyplot import setp
from drawnow import *
#import time
#import sys
import csv


# Object creation
temp_array = []
humidity_array = []
heatIndex_array = []
cont = 0
min10_Count = 0
datalog_count = 0

ardunioData = serial.Serial('/dev/ttyACM0', 9600)

# interactive mode = true by this code
plt.ion()


# Create funtion that make graph
def makeFig():
    redline = plt.plot(temp_array, 'r-')
    blueline = plt.plot(humidity_array, 'b-')
    greenline = plt.plot(heatIndex_array, 'g-')
    setp(redline, linewidth=2)  # setting the width of the temperature line
    setp(greenline, linestyle='--')  # setting the style for heatindex line
    plt.grid()
    plt.xlabel("Time")
    plt.legend()


# Funktion Window
def windowStatus(init, angular):
    pass


# Funktion for heater
def heaterStatus(param):
    pass


# main program
while True:
    while ardunioData.inWaiting() == 0:
        pass

    # Read the line from arduino and change into string
    # noinspection PyBroadException
    try:
        arduinoString = str(ardunioData.readline().decode('utf-8'))
        data = arduinoString.split(',')
    except:
        print("DataError!")

    # String to float conversion
    # noinspection PyBroadException
    try:
        single_humidity = float(data[0])
    except:
        print("DataError in Humidity")
    # noinspection PyBroadException
    try:
        single_temperature = float(data[1])
    except:
        print("DataError in Temperature")
    # noinspection PyBroadException
    try:
        heatIndex = float(data[2])
    except:
        print("DataError in HeatIndex")

    # Store float data into array
    # noinspection PyBroadException
    try:
        temp_array.append(single_temperature)
    except:
        print("Couldnt define single_temperature")
        temp_array.append(0)

    # noinspection PyBroadException
    try:
        humidity_array.append(single_humidity)
    except:
        print("Couldnt define single_humidity")
        humidity_array.append(0)
    # noinspection PyBroadException
    try:
        heatIndex_array.append(heatIndex)
    except:
        print("Couldnt define heatIndex")
        heatIndex_array.append(0)

    # Call Drawnow to update the live graph
    drawnow(makeFig)
    plt.pause(0.0001)

    with open("Data/Excels/Data.csv", "a")as log:
        logWriter = csv.writer(log)
        logWriter.writerow([single_temperature, single_humidity, heatIndex])

    min10_Count += 1

    if min10_Count >= 600:
        datalog_count += 1
        plt.savefig('Data/Graphs/10MinsDatas(%d).pdf' % datalog_count)

        min10_Count = 0
        temp_array.clear()
        humidity_array.clear()
        heatIndex_array.clear()

    log.close()
