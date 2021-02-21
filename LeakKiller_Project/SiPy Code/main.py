import pycom
import os
from machine import SD
from machine import Timer
from machine import SPI
from machine import Pin
from machine import I2C
from _LCD import LCDBackend
from _RTC import RTCBackend
from _CAN_CANBUS import CAN_M
from _CAN_CANBUS import CAN_Backend

# Initialise LED
pycom.heartbeat(False)
pycom.rgbled(0xff00)  # green 

# Pin and Com definitions
_SPI_Ref = SPI(0, mode=SPI.MASTER, baudrate=100000, polarity=0, phase=0, firstbit=SPI.MSB)
_I2C_Ref = I2C(0, I2C.MASTER, baudrate=10000, pins=('P21','P20')) # SDA, SCL
_LCD_CS_Ref = Pin('P9', mode=Pin.OUT)
_CAN_CS_Ref = Pin('P3', mode=Pin.OUT)
_FlowMeter = Pin('P15', mode=Pin.IN)
_Solenoid = Pin('P19', mode=Pin.OUT)

# Calling Constructors
_LCDScreen = LCDBackend(_SPI_Ref, _LCD_CS_Ref)
_Message = CAN_M()
_Nodes = CAN_Backend(0x00, _SPI_Ref, _CAN_CS_Ref)
_Clock = RTCBackend(_I2C_Ref)
_BT_UART = UART(1, baudrate=9600, pins=('P7','P6')) # TX, RX

#_Clock.SetTime(0, 42, 11, 7, 26, 11, 17)

# SD stuff
sd = SD()
os.mount(sd, '/sd')

RootDir = "/sd/Watermeter"
ProfilerDirectory = "/Profiler"
ErrorDirectory = "/ErrorLogs"

try:  # there is no check directory member of uos module...
    os.mkdir(RootDir)
except:
    print("Directory Exists")
try:
    os.mkdir(RootDir + ProfilerDirectory)
except:
    print("Directory Exists")
try:
    os.mkdir(RootDir + ErrorDirectory)
except:
    print("Directory Exists")

def MonitorFlow(): # 1Litre = 596 pulses 
    TotalDelay = 0
    TickCounter = 0 
    PulseLogic = _FlowMeter()
    while (TotalDelay < 1000000): # 1 second delay
        Reading = _FlowMeter()
        if((Reading > PulseLogic)): # rising edge
            TickCounter += 1
        PulseLogic = Reading
        TotalDelay += 50
        Timer.sleep_us(50)
    LitresPerMinute = round((TickCounter/10),2)
    return LitresPerMinute # Litres/Min
    

def BTDataHandler(LocalFlow, LocalIsoStat, LocalNodeID, LocalNodeStat):
    global CurrentIsolationCode
    BT_DataFlow = int((int(LocalFlow) * int(100))) # gives floating point resolution cast as an integer x 100. cast as int to negate overflow errors
    BT_DataFlow_LSB = (BT_DataFlow & 0xFF)
    BT_DataFlow_MSB = ((BT_DataFlow << 8) & 0xFF)

    BT_IsoStat = (LocalIsoStat & 0xFF) # mask to byte # isolation status 0x00 is no error and solenoid inactive (free water flow) anything else is a specific error and solenoid active (blocked flow)

    BT_NodeID_LSB = (LocalNodeID & 0xFF)
    BT_NodeID_MSB = ((LocalNodeID >> 8) & 0x07) # masks 11 bits
    BT_NodeID_Stat = LocalNodeStat

    BT_TXData = bytes([BT_DataFlow_LSB,BT_DataFlow_MSB,BT_IsoStat,BT_NodeID_LSB,BT_NodeID_MSB,BT_NodeID_Stat])

    if(_BT_UART.any() > 0):
        Request = _BT_UART.read(1) # read the first byte
        if(Request == b'A'):
            _BT_UART.write(BT_TXData)
        elif(Request == b'B'): # activate isolator
            pycom.rgbled(0x7f0000) # red
            _Solenoid(True)
            CurrentIsolationCode = 0x04 
        elif(Request == b'C'): # deactivate isolator
            pycom.rgbled(0x007f00) # green
            _Solenoid(False)
            CurrentIsolationCode = 0x00
    while(_BT_UART.any() > 3): # clears any backlog in the buffer
            BT_UART.read(_BT_UART.any())


def NodeListener(): # Passively listen for incoming errors
    X = CAN_M()
    while (_Nodes.Get_Message(X)):
        if(X.Data_7 != 0xFF): # data_7 is the master-ignore status flag
            global CurrentErrorNode
            global CurrentErrorNodeData
            global CurrentIsolationCode
            CurrentErrorNode = X.ID
            CurrentErrorNodeData = X.Data_0
            _ErrorCode = str(X.ID) + "_" + str(X.Data_0) # error code generated from Node ID and Sensor flag byte
            pycom.rgbled(0x7f7f00) # yellow
            CurrentIsolationCode = 0x03
            _Solenoid(True)
            F = open(RootDir + ErrorDirectory + "/" + "NodeErrors.txt", 'a')
            F.write(_ErrorCode)
            F.write(" , ")
            F.write(TimeStampString())
            F.write("\r\n") # carriage return
            F.close()
            pycom.rgbled(0x7f7f00) # yellow
            return _ErrorCode

def UpdateLCD(LocalWaterflow,LocalLeakyNodes):
    _LCDScreen.ClearScreen()
    _LCDScreen.WriteLine1("Flow: " + str(LocalWaterflow) + " L/m")
    _LCDScreen.WriteLine2("Node: " + str(LocalLeakyNodes))

def TimeStampString(): # returns a string of the time
    _TimeStamp = ""
    _TimeStamp += str(_Clock.ReadSecond())
    _TimeStamp += ":"
    _TimeStamp += str(_Clock.ReadMinute())
    _TimeStamp += ":"
    _TimeStamp += str(_Clock.ReadHour())
    _TimeStamp += " , "
    _TimeStamp += str(_Clock.ReadDate())
    _TimeStamp += ":"
    _TimeStamp += str(_Clock.ReadMonth())
    _TimeStamp += ":"
    _TimeStamp += str(_Clock.ReadYear())
    return _TimeStamp

def FlowProfiler(LocalClock , LocalAverage):
    if(LocalClock.ReadMinute() == 0):
        F = open(RootDir + ProfilerDirectory + "/" + str(LocalClock.ReadHour()) + ".txt", "w")
    else:
        F = open(RootDir + ProfilerDirectory + "/" + str(LocalClock.ReadHour()) + ".txt", "a")
    
    if(LocalClock.ReadSecond() == 0):
        F.write(str(LocalClock.ReadMinute()))
        F.write(" , ")
        temp = 0
        for x in range(0, 60):
            temp += LocalAverage[x]
        temp /= 60.0
        temp = round(temp,3)
        F.write(str(temp))
        F.write("\r\n") # carriage return
    F.close()

def Anomaly_MaxFlowWatcher(LocalFlow):
    if(LocalFlow > 7):
        _Solenoid(True) # shuts the water and power off.
        pycom.rgbled(0x7f0000) # red
        return 0x01 # isolator trigger code
    else:
        return None

def Anomaly_TrickleFlowWatcher(LocalAverage): # for monitoring if taps have not been turned off properly or for hairline cracks/leaks (uses minute rolling average)
    TrickleTrigger = True
    for x in range(0, 60):
        if(LocalAverage[x] == 0): # if there is a point of zero flow = no leak or tap left on
            TrickleTrigger = False
            break
        if(LocalAverage[x] > 0.9): # checking for a non-zero continuous small flow over a minute 
            TrickleTrigger = False
            break
    if(TrickleTrigger == True):
        _Solenoid(True) # shuts the water and power off.
        pycom.rgbled(0x7f0000) # red
        return 0x02 # isolator trigger code
    else:
        return None # no trigger code

# MAIN CODE
print("Intialised")
# Global Variables
RollingAverage = [0]*60 # array of 60 elements (60 seconds)
ErrorCode = "_"
CurrentIsolationCode = 0x00 # status code of the solenoid/relay detailing if/how the isolation was tiggered
CurrentErrorNode = 0
CurrentErrorNodeData = 0
while True:
    CurrentFlowRate = MonitorFlow()
    RollingAverage[_Clock.ReadSecond()] = CurrentFlowRate # updates the average minute flow for use with the flow watchers

    ErrorTemp = NodeListener()
    if(ErrorTemp != None):
        ErrorCode = ErrorTemp
    
    UpdateLCD(CurrentFlowRate, ErrorCode)

    FlowProfiler(_Clock, RollingAverage)

    TempAM = Anomaly_MaxFlowWatcher(CurrentFlowRate)
    if(TempAM != None):
        CurrentIsolationCode = TempAM

    TempAT = Anomaly_TrickleFlowWatcher(RollingAverage)
    if(TempAT != None):
        CurrentIsolationCode = TempAT

    BTDataHandler(CurrentFlowRate,CurrentIsolationCode,CurrentErrorNode,CurrentErrorNodeData)