class MCP2515_Reg:

    #-----------------------------------------------------------------#
    # Core Instructions
    #-----------------------------------------------------------------#
    
    WRITE = 0x02
    READ = 0x03
    BITMODIFY = 0x05
    READSTATUS = 0xA0
    RESET = 0xC0
    REQUESTTOSEND = 0x80
    
    #-----------------------------------------------------------------#
    # Registers
    #-----------------------------------------------------------------#
    
    #-----------------------------------------------------------------#
    # TX REGISTERS
    #-----------------------------------------------------------------#
    
    # TRANSMIT BUFFER 0 CONTROL REGISTER
    TXB0CTRL = 0x30
    
    # TRANSMIT BUFFER 1 CONTROL REGISTER
    TXB1CTRL = 0x40
    
    # TRANSMIT BUFFER 2 CONTROL REGISTER
    TXB2CTRL = 0x50
    
    # TX0RTS PIN CONTROL AND STATUS REGISTER
    TXRTSCTRL = 0x0D
    
    # TRANSMIT BUFFER 0 STANDARD IDENTIFIER HIGH
    TXB0SIDH = 0x31
    
    # TRANSMIT BUFFER 1 STANDARD IDENTIFIER HIGH
    TXB1SIDH = 0x41
    
    # TRANSMIT BUFFER 2 STANDARD IDENTIFIER HIGH
    TXB2SIDH = 0x51
    
    # TRANSMIT BUFFER 0 STANDARD IDENTIFIER LOW
    TXB0SIDL = 0x32
    TXB0SIDL_Mask_EXIDE = 0x08
    TXB0SIDL_Mask_TXB0SIDL_EID = 0x07
    TXB0SIDL_Mask_TXB0SIDL_SID = 0xE0
    
    # TRANSMIT BUFFER 1 STANDARD IDENTIFIER LOW
    TXB1SIDL = 0x42
    TXB1SIDL_Mask_EXIDE = 0x08
    TXB1SIDL_Mask_TXB1SIDL_EID = 0x07
    TXB1SIDL_Mask_TXB1SIDL_SID = 0xE0
    
    # TRANSMIT BUFFER 2 STANDARD IDENTIFIER LOW
    TXB2SIDL = 0x52
    TXB2SIDL_Mask_EXIDE = 0x08
    TXB2SIDL_Mask_TXB2SIDL_EID = 0x07
    TXB2SIDL_Mask_TXB2SIDL_SID = 0xE0
    
    # TRANSMIT BUFFER 0 EXTENDED IDENTIFIER HIGH
    TXB0EID8 = 0x33
    
    # TRANSMIT BUFFER 1 EXTENDED IDENTIFIER HIGH
    TXB1EID8 = 0x43

    # TRANSMIT BUFFER 2 EXTENDED IDENTIFIER HIGH
    TXB2EID8 = 0x53

    # TRANSMIT BUFFER 0 EXTENDED IDENTIFIER LOW
    TXB0EID0 = 0x34
    
    # TRANSMIT BUFFER 0 EXTENDED IDENTIFIER LOW
    TXB1EID0 = 0x44

    # TRANSMIT BUFFER 0 EXTENDED IDENTIFIER LOW
    TXB2EID0 = 0x54

    # TRANSMIT BUFFER 0 DATA LENGTH CODE
    TXB0DLC = 0x35
    TXB0DLC_Mask_RTR = 0x20
    TXB0DLC_Mask_DLC = 0x0F

    # TRANSMIT BUFFER 1 DATA LENGTH CODE
    TXB1DLC = 0x45
    TXB1DLC_Mask_RTR = 0x20
    TXB1DLC_Mask_DLC = 0x0F

    # TRANSMIT BUFFER 2 DATA LENGTH CODE
    TXB2DLC = 0x55
    TXB2DLC_Mask_RTR = 0x20
    TXB2DLC_Mask_DLC = 0x0F

    # Data
    
    # TX0 Data
    TXB0D0 = 0x36
    TXB0D1 = 0x37
    TXB0D2 = 0x38
    TXB0D3 = 0x39
    TXB0D4 = 0x3A
    TXB0D5 = 0x3B
    TXB0D6 = 0x3C
    TXB0D7 = 0x3D

    # TX1 Data
    TXB1D0 = 0x46
    TXB1D1 = 0x47
    TXB1D2 = 0x48
    TXB1D3 = 0x49    
    TXB1D4 = 0x4A
    TXB1D5 = 0x4B
    TXB1D6 = 0x4C
    TXB1D7 = 0x4D
    
    # TX2 Data
    TXB2D0 = 0x56
    TXB2D1 = 0x57
    TXB2D2 = 0x58
    TXB2D3 = 0x59
    TXB2D4 = 0x5A
    TXB2D5 = 0x5B
    TXB2D6 = 0x5C
    TXB2D7 = 0x5D
    
    #-----------------------------------------------------------------#
    # RX REGISTERS
    #-----------------------------------------------------------------#
    
    # RECEIVE BUFFER 0 CONTROL
    RXB0CTRL = 0x60
    RXB0CTRL_Mask_RXM = 0x60 # Opperation Mode Bits

    # RECEIVE BUFFER 1 CONTROL
    RXB1CTRL = 0x70
    RXB1CTRL_Mask_RXM = 0x60 # Opperation Mode Bits

    # RXnBF PIN CONTROL AND STATUS
    BFPCTRL = 0x0C

    # RECEIVE BUFFER 0 STANDARD IDENTIFIER HIGH
    RXB0SIDH = 0x61

    # RECEIVE BUFFER 1 STANDARD IDENTIFIER HIGH
    RXB1SIDH = 0x71

    # RECEIVE BUFFER 0 STANDARD IDENTIFIER LOW
    RXB0SIDL = 0x62
    RXB0SIDL_Mask_IDE = 0x08

    # RECEIVE BUFFER 1 STANDARD IDENTIFIER LOW
    RXB1SIDL = 0x72
    RXB1SIDL_Mask_IDE = 0x08

    # RECEIVE BUFFER 0 EXTENDED IDENTIFIER HIGH
    RXB0EID8 = 0x63

    # RECEIVE BUFFER 1 EXTENDED IDENTIFIER HIGH
    RXB1EID8 = 0x73

    # RECEIVE BUFFER 0 EXTENDED IDENTIFIER LOW
    RXB0EID0 = 0x64

    # RECEIVE BUFFER 0 EXTENDED IDENTIFIER LOW
    RXB1EID0 = 0x74

    # RECEIVE BUFFER 0 DATA LENGTH CODE
    RXB0DLC = 0x65

    # RECEIVE BUFFER 1 DATA LENGTH CODE
    RXB1DLC = 0x75
    
    # RECEIVE BUFFER 0 DATA
    RXB0D0 = 0x66
    RXB0D1 = 0x67
    RXB0D2 = 0x68
    RXB0D3 = 0x69
    RXB0D4 = 0x6A
    RXB0D5 = 0x6B
    RXB0D6 = 0x6C
    RXB0D7 = 0x6D

    # RECEIVE BUFFER 1 DATA
    RXB1D0 = 0x76
    RXB1D1 = 0x77
    RXB1D2 = 0x78
    RXB1D3 = 0x79
    RXB1D4 = 0x7A
    RXB1D5 = 0x7B
    RXB1D6 = 0x7C
    RXB1D7 = 0x7D

    #-----------------------------------------------------------------#
    # BIT TIMING REGISTERS
    #-----------------------------------------------------------------#

    # CONFIGURATION 1
    CNF1 = 0x2A
    CNF1_Mask_BRP = 0x3F
    CNF1_Mask_SJW = 0xC0

    # CONFIGURATION 2
    CNF2 = 0x29
    CNF2_Mask_BTLMODE = 0x80 # PS2 Mode bit
    CNF2_Mask_SAM = 0x40 # Sample point config bit
    CNF2_Mask_PHSEG1 = 0x38 # PS1 length bits
    CNF2_Mask_PRSEG = 0x07 # propigation segment length bits

    # CONFIGURATION 3
    CNF3 = 0x28
    CNF3_Mask_PHSEG2 = 0x07 # ps2 length bits
    CNF3_Mask_SOF = 0x80 # start of frame pin enable bit
    CNF3_Mask_WAKFIL = 0x40 # wake up filter mode bit

    #-----------------------------------------------------------------#
    # ERROR COUNTING REGISTERS
    #-----------------------------------------------------------------#

    # TRANSMIT ERROR COUNTER
    TEC = 0x1C

    # RECEIVER ERROR COUNTER
    REC = 0x1D

    # ERROR FLAG
    EFLG = 0x2D

    #-----------------------------------------------------------------#
    # INTERUPT REGISTERS
    #-----------------------------------------------------------------#

    # INTERRUPT ENABLE
    CANINTE = 0x2B

    # INTERRUPT FLAG
    CANINTF =0x2C
    CANINTF_Mask_RX0IF = 0x01
    CANINTF_Mask_RX1IF = 0x02
    CANINTF_Mask_MERRF = 0x80
    CANINTF_Mask_TX0IF = 0x04
    CANINTF_Mask_TX1IF = 0x08
    CANINTF_Mask_TX2IF = 0x10

    #-----------------------------------------------------------------#
    # MODES OF OPPERATION
    #-----------------------------------------------------------------#

    # XF // CAN CONTROL REGISTER
    CANCTRL = 0x0F
    CANCTRL_Mask_REQOP = 0xE0 # set opperation mode
    CANCTRL_Mask_CLKPRE = 0x03 # clock pin pre-scaler
    CANCTRL_Mask_CLKEN = 0x04 # clockout pin enable bit
    CANCTRL_Mask_OSM = 0x08 # TX one shot mode

    # XE // CAN STATUS REGISTER
    CANSTAT = 0x0E