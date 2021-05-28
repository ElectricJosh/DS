# https://docs.pycom.io/firmwareapi/pycom/machine/sd/

# https://docs.pycom.io/firmwareapi/pycom/expansionboards/l76gnss/

# https://development.pycom.io/pytrackpysense/apireference/pytrack/

# https://docs.pycom.io/chapter/pytrackpysense/installation/firmware.html

# Make sure every library is version 1

# See: https://github.com/pycom/pycom-libraries/tree/148a43996b415ae9ee5dce6a7b7a26944f300635/shields

# https://support.google.com/mymaps/answer/3024925
# Add CSV points to google maps super easy



# Timer
import time

# SD Card
import os
import machine
from machine import SD

# GPS
from L76GNSS import L76GNSS
from pycoproc_1 import Pycoproc

# GPS Constructor
GPS = L76GNSS(Pycoproc(Pycoproc.PYTRACK), timeout=30)

# Mount SD Card
sd = SD()
os.mount(sd, '/sd')

FileNo = 0
FileName = ''
while True: # Find a unique file number
    try:
        FileName = '/sd/' + str(FileNo) + '.csv'
        FileNo = FileNo + 1
        open(FileName, 'r')
    except:
        break


f = open(FileName, 'a')
f.write('Name,' + 'Latitude,' + 'Longitude' + '\r\n') # Add column names for an easier import into Google Maps
f.close()



GPS_Store = ''

while(True):
    location = GPS.coordinates() # Latitude, Longitude Tuple 

    if location == GPS_Store: # Filter Duplicate Data
        time.sleep(5)
        continue

    if location == (None, None): # Filter Empty Data
        time.sleep(5)
        continue

    GPS_Store = location # Update Historical Data    

    latitude = location[0]
    longitude = location[1]
    
    f = open(FileName, 'a') # Use append mode
    f.write('Fix,' + str(latitude) + ',' + str(longitude) + '\r\n')
    f.close()

    print(location)
    time.sleep(5)


    # Works perfectly