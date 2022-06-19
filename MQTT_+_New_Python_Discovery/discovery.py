import socket
import struct
import sys

multicast_group = '233.3.3.3'
server_address = ('', 33333)

# Create the socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Bind to the server address
sock.bind(server_address)

###

# Tell the operating system to add the socket to the multicast group
# on all interfaces.
group = socket.inet_aton(multicast_group)
mreq = struct.pack('4sL', group, socket.INADDR_ANY)
sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)

###

# Receive/respond loop
while True:
    print("Waiting to receive message..")
    data, address = sock.recvfrom(1024)

    print("received %s bytes from %s" % (len(data), address))
    print(data)

    f = open("ip.txt", "w")
    f.write(str(address[0]))
    f.close()
