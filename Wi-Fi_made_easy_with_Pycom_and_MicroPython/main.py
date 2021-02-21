# https://docs.pycom.io/firmwareapi/pycom/network/wlan/
# WLAN Reference

# https://docs.micropython.org/en/latest/library/usocket.html
# Sockets Reference

# https://docs.pycom.io/datasheets/expansionboards/expansion2/
# Board Layout

import network
import usocket
import machine
import time


# Setup test input pin
button_state = machine.Pin("G17", mode=machine.Pin.IN, pull=machine.Pin.PULL_UP)

# Setup WiFi
JoshyLAN = network.WLAN(mode=network.WLAN.STA) # Set radio to station mode
JoshyLAN.ifconfig(config="dhcp") # Use automatic IP address allocation when connected

# Scan for available networks and attempt to connect
JoshyLAN.scan() 
JoshyLAN.connect("Josh's Super WiFi Booster (2.4)", auth=(network.WLAN.WPA2, "w4w6pQybhAQv"), timeout=None)

# Wait for connection
while not JoshyLAN.isconnected(): 
    print("Connecting...")
    time.sleep(1)
print("Connected to WiFi network")


# Setup Sockets
JoshySocket = usocket.socket(usocket.AF_INET, usocket.SOCK_STREAM, usocket.IPPROTO_TCP) # establish standard IP socket
JoshySocket.bind((JoshyLAN.ifconfig()[0],100)) # bound socket to local IP and random port
print("IP address " + str(JoshyLAN.ifconfig()[0]) + ", Port " + str(100)) # prints IP and Port number to be used by Putty.

while True:
    print("Listening for connection")
    JoshySocket.listen() # Blocking function # Listen on socket for incoming connection
    PuttySocket = JoshySocket.accept()[0] # Accepts latest connection and gets socket object
    print("Connection accepted")

    while True:
        try:
            PuttySocket.send(str(button_state.value())+"\r\n") # send button data until socket is closed
            time.sleep(1)
        except:
            print("Connection closed")
            break