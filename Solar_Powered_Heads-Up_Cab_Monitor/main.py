
import time
import pycom
import machine
from machine import Pin

from LIS2HH12 import LIS2HH12
from SI7006A20 import SI7006A20
from LTR329ALS01 import LTR329ALS01
from MPL3115A2 import MPL3115A2,ALTITUDE,PRESSURE
from pycoproc_1 import Pycoproc

py = Pycoproc(Pycoproc.PYSENSE) # Expansion board object

#pres = MPL3115A2(py, mode=PRESSURE) # Returns pressure in Pa. Mode may also be set to ALTITUDE, returning a value in meters

dht = SI7006A20(py) # Temperature, Relative humidity and dew point

li = LTR329ALS01(py) # Light





pycom.heartbeat(False) # Turn off flashing
pycom.rgbled(0x00) # Off

Wake_Input = Pin('P10', mode=Pin.IN, pull=Pin.PULL_UP) # polling because interupts brick my system
# P14 is the pysense button

# Solar State Machine
while True: 
    if not Wake_Input(): # active low for testing
        print("Wake")

        Cab_T = dht.temperature() # deg C
        Cab_RH = dht.humidity() # % relative Humidity
        Cab_L = li.light()[1] # Red Light Lux

        print("Temperature: " + str(Cab_T) + " C") # 20 degres is warm, 25 is too hot
        print("Relative Humidity: " + str(Cab_RH) + " %") # 50 is humid # 60 might become uncomfotable
        print("Red Light: " + str(Cab_L) + " Lux") # 500 is overcast, only program as a warning
        # Green for good, yellow for warning, red for bad

        if (Cab_T > 25) or (Cab_RH > 50) or (Cab_L < 500): # check for warm, humid and overcast conditions (muggy/drowsy)
            if (Cab_T > 30) or (Cab_RH > 60): # Check for hot and sticky conditions (uncomfortable/accelerated fatigue)
                pycom.rgbled(0xff0000) # Red
            else:
                pycom.rgbled(0x0000ff) # Blue
        else:
            pycom.rgbled(0x00ff00) # Green

        time.sleep(1) # Flash LED for a second
        pycom.rgbled(0x00) # Turn off
        time.sleep(2) # Sleep for 2 seconds (3 second duty cycle)

    else:
        print("Sleep")
        pycom.rgbled(0x00) # Off
        time.sleep(10) # Sleep for longer to conserve power