__author__ = 'darwin'
# This program is created to be the server

import socket
import sys

#create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)


#Bind the socker to the part
ser_address = ("192.168.1.19", 10000)
print( sys.stderr, 'starting up on %s port %s' % ser_address)
sock.bind(ser_address)

#Caling listen() puts the socker into server mode and accept() waiting for an incoming connection


#Listen for incoming connections
sock.listen(1)

while True:
    #wait for a connection
    print(sys.stderr, 'waiting for a connection')
    connection, client_address = sock.accept()


#accept(9 returns an open connection between the server and client , along with the address of the client.
# The connection is actually a different socket on another port(assigned by the kernel).
# Data is read from the connection with recv() and transmitted with senda11().

try:
    print(sys.stderr, 'connection from', client_address)

    # Recieve the data in small chunks and retransmit it
    while True:
        bytedata = connection.recv(16)
        data = bytedata.encode("utf8")
        print(sys.stderr,'recieved "%s" ' % data)
        if data :
            print(sys.stderr, 'sending data back to the client')
            connection.sendall(bytedata)
        else:
            print(sys.stderr,'no more data from',client_address)
            break
finally:
    #clean up the connection
    connection.close()

