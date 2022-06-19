#Discovery protocol by team PUB

import socket
import struct
import sys
import time
import threading
from texttable import Texttable

multicast_group = '233.3.3.3'
server_address = ('', 33333)

# Create the socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Bind to the server address
sock.bind(server_address)

# Tell the operating system to add the socket to the multicast group on all interfaces.
group = socket.inet_aton(multicast_group)
mreq = struct.pack('4sL', group, socket.INADDR_ANY)
sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)
sock.settimeout(10)

#global variable
brojac = 0

class Ventilator:
  def __init__(self):
    self.state = 0
    self.ip = ("","")

class Sensor:
    def __init__(self):
        self.state = 0
        self.ip = ("","")

class Laptop:
  def __init__(self):
    self.state = 0
    self.ip = ("","")


#receive the data from clients 10 times per second(10 FPS)
def receive():
    #set the timer
    threading.Timer(1/10, receive).start()

    #receive data from client/s
    try:
        data, address = sock.recvfrom(1024)
    except socket.timeout:
        return

    #get the useful information
    ret = data.split(":".encode())
    id = ret[0].decode()

    #set the flags
    if id == "0" and ventilator.state == 0:
        ventilator.state = 1
        ventilator.ip = address
    elif id == "1" and sensor.state == 0:
        sensor.state = 1
        sensor.ip = address
    elif id == "2" and laptop.state == 0:
        laptop.state = 1
        laptop.ip = address

        # send back the ack message to laptop
        sock.sendto('ack'.encode(), laptop.ip)

#once in 5 seconds, check the paired devices(1/5 FPS)
def check():
    global brojac

    brojac += 1

    #set the timer
    threading.Timer(5.0, check).start()

    #print paired devices
    print_table()

    # reset the flags
    ventilator.state = 0
    sensor.state = 0
    laptop.state = 0

#print paired devices
def print_table():
    global brojac

    print("Report No:{0}".format(brojac))

    t = Texttable()
    t.add_rows([['Devices', 'State', 'IP Adress'], ['Ventilator', state(ventilator.state), ventilator.ip[0]],
                                                   ['Sensor', state(sensor.state), sensor.ip[0]],
                                                   ['Laptop', state(laptop.state), laptop.ip[0]]])
    print(t.draw())

    for i in range (3):
        print("")

    print("+-------------------------------------+")

    for i in range (3):
        print("")

#returns the state of the device
def state(x):
    if x == 0:
        return "OFF"
    else:
        return "ON"

#the main thread
if __name__ == "__main__":
    ventilator = Ventilator()
    sensor = Sensor()
    laptop = Laptop()

    receive()
    check()