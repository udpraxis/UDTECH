__author__ = 'udlab'
from twisted.internet.protocol import Factory, Protocol
from twisted.internet import reactor

class IphoneChat(Protocol):
        def connectionMade(self):
            self.factory.clients.append(self)
            print(" clients are ", self.factory.clients)

        def connectionLost(self, reason):
            self.factory.clients.remove(self)

        def dataReceived(self, data):
            decodedata = bytes.decode(data,'utf-8')
            a = decodedata.split(':')

            print(a)

            if len(a) > 1:
                command = a[0]
                content = a[1]

                msg = ""
                if command == "iam":
                    self.name = content
                    msg = self.name + " has joined "
                    bytemsg = str.encode(msg)

                elif command == "msg":
                    msg = self.name + " : " + content
                    bytemsg = str.encode(msg)

                elif command == "exit":
                    msg = self.name + " : " + content
                    bytemsg = str.encode(msg)

                for c in self.factory.clients:
                    c.message(msg)

        def message(self, message):
            # the transmission is in byte
            byteMessage = str.encode(message)
            self.transport.write(byteMessage)

        def exitCommand(self, message):
            #The msg to say exit status
            byteMessage = str.encode(message)
            self.transport.write(byteMessage)
            self.factory.clients.remove()

factory = Factory()
factory.clients = []
factory.protocol = IphoneChat
reactor.listenTCP(8000, factory)
print("Iphone Chat server started")
reactor.run()