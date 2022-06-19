import socket
import struct
import sys
import time, threading
from pynput.keyboard import Key, Listener, Controller

flag = 0

def on_press(key):
    global flag
    try:
        if key.char == "q":
            flag = 1
    except AttributeError:
        if key == "q":
            flag = 1

listener = Listener(on_press=on_press)
listener.start()
keyboard = Controller()

message = '1:temp:moisture'
multicast_group = ('233.3.3.3', 33333)

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.settimeout(0.5)
#Set the time-to-live for messages to 1 so they do not go past the local network segment.
ttl = struct.pack('b', 1)
sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, ttl)

# threading.Timer(5, send).start()

while 1:
    print("sending {0}".format(message))

    try:
        if flag == 0:
            sent = sock.sendto(message.encode(), multicast_group)
            time.sleep(1)
            continue
        else:
            break
    except:
        continue

print("closing socket")
sock.close()
