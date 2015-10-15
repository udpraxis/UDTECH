__author__ = 'darwin'
import  socket
import sys

#create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect the socket to the port where the server is listening
ser_address = ("192.168.1.19", 10000)
print(sys.stderr, 'connection to %s port %s' % ser_address)
sock.connect(ser_address)

try:
    # Send data
    message = 'This is the message . It will be repeated.'
    print(sys.stderr, 'sending "%s" ' % message)
    sock.sendall(bytes(message, 'utf8'))

    #Look for the response
    amount_recieved = 0
    amount_expected = len(message)

    while amount_recieved < amount_expected:
        bytedata = sock.recv(16)
        data = bytedata.encode('utf8')
        amount_recieved += len(data)
        print(sys.stderr,'recieved "%s" ' % data)
finally:
    print(sys.stderr, 'closing socket')
    sock.close()
