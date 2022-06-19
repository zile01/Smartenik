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

def send():
    # Send data to the multicast group
    print("sending {0}".format(message))
    sent = sock.sendto(message.encode(), multicast_group)
    time.sleep(1)

    while True:
        # print("waiting to receive ack")
        try:
            data, server = sock.recvfrom(16)
        except socket.timeout:
            print("timed out no more responses")
            break
        else:
            print("received {0} from {1}".format(data, server))


multicast_group = ('233.3.3.3', 33333)

message = '2:ON'
multicast_group = ('233.3.3.3', 33333)

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.settimeout(0.5)
#Set the time-to-live for messages to 1 so they do not go past the local network segment.
ttl = struct.pack('b', 1)
sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, ttl)

# threading.Timer(5, send).start()

while 1:
    try:
        if flag == 0:
            send()
            continue
        else:
            break
    except:
        continue

print("closing socket")
sock.close()
