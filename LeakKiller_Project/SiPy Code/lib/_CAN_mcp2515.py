from _CAN_mcp2515_registers import MCP2515_Reg
from machine import SPI
from machine import Pin

class MCP2515Backend:

    MCP2515_Serial = 0
    MCP2515_CS_Pin = 0

    def __init__(self, SPI_Object, CS_Object): # initialise on default SPI channel.
        self.MCP2515_Serial = SPI_Object
        self.MCP2515_CS_Pin = CS_Object

    def MCP2515_CS_Enable(self):
        self.MCP2515_CS_Pin(False) # Active Low

    def MCP2515_CS_Disable(self):
        self.MCP2515_CS_Pin(True) # Active Low

    def MCP2515_Reset(self):
        self.MCP2515_CS_Disable() 
        self.MCP2515_CS_Enable() 
        self.MCP2515_Serial.write(bytes([MCP2515_Reg.RESET])) # bytes array defintion of size 1 
        self.MCP2515_CS_Disable()
        
    # Read Status Register # contains the most common status flags for convenience.

    def MCP2515_Read_Status(self):
        self.MCP2515_CS_Disable()
        self.MCP2515_CS_Enable()
        rbuf = bytearray(2)
        self.MCP2515_Serial.write_readinto(bytes([MCP2515_Reg.READSTATUS, 0xFF]), rbuf) # write bytes then read to buffer 
        STATUS = rbuf[1] # read last byte
        self.MCP2515_CS_Disable()
        return STATUS        
        
    # Read Single Register
        
    def MCP2515_Read(self, address):
        self.MCP2515_CS_Disable()
        self.MCP2515_CS_Enable()
        rbuf = bytearray(3)
        self.MCP2515_Serial.write_readinto(bytes([MCP2515_Reg.READ, address, 0xFF]), rbuf)
        STATUS = rbuf[2] # read last byte
        self.MCP2515_CS_Disable()
        return STATUS
        
    # Write Single Register

    def MCP2515_Write(self, address, data):
        self.MCP2515_CS_Disable()
        self.MCP2515_CS_Enable()
        self.MCP2515_Serial.write(bytes([MCP2515_Reg.WRITE, address, data]))
        self.MCP2515_CS_Disable()
        
    # Modify a single bit of a single register
    
    def MCP2515_Bit_Modify(self, address, mask, data):
        self.MCP2515_CS_Disable()
        self.MCP2515_CS_Enable()
        self.MCP2515_Serial.write(bytes([MCP2515_Reg.BITMODIFY, address, mask, data]))
        self.MCP2515_CS_Disable()
        
    # Request to send selected tx buffers

    def MCP2515_TX_Request_To_Send(self, TX0, TX1, TX2): 
        self.MCP2515_CS_Disable()
        self.MCP2515_CS_Enable() 
        RTS = MCP2515_Reg.REQUESTTOSEND
        if (TX0 == True):
            RTS = (RTS | self.MCP2515_Mask_Finder(0))
        if (TX1 == True):
            RTS = (RTS | self.MCP2515_Mask_Finder(1))
        if (TX2 == True):
            RTS = (RTS | self.MCP2515_Mask_Finder(2))
        
        self.MCP2515_Serial.write(RTS)
        self.MCP2515_CS_Disable()
        
    # Bitwise Mask Finder

    def MCP2515_Mask_Finder(self, bit_no):# Bit number is 0 - 7
        return pow(2, bit_no)

    # Bitwise Byte Interpreter

    def MCP2515_Find_Bit(self, x, bit_no): # Bit number is 0 - 7

        mask = pow(2, bit_no)  
        x = x & mask
        x = x >> bit_no
    
        return (x > 0)