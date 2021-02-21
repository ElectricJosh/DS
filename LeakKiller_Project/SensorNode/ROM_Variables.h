#ifndef ROM_Variables_h
#define ROM_Variables_h

// Core Instructions
#define WRITE 0x02
#define READ 0x03
#define BITMODIFY 0x05
#define READSTATUS 0xA0
#define RESET 0xC0
#define REQUESTTOSEND 0x80 // Tx send request add bits to send up to all three buffers

// Registers

// TX REGISTERS
//-----------------------------------------------------------------//

// TRANSMIT BUFFER 0 CONTROL REGISTER
#define TXB0CTRL 0x30
// -- Masks underneith

// TRANSMIT BUFFER 1 CONTROL REGISTER
#define TXB1CTRL 0x40
// -- Masks underneith

// TRANSMIT BUFFER 2 CONTROL REGISTER
#define TXB2CTRL 0x50
// -- Masks underneith

// TX0RTS PIN CONTROL AND STATUS REGISTER
#define TXRTSCTRL 0x0D
// -- Masks underneith

// TRANSMIT BUFFER 0 STANDARD IDENTIFIER HIGH
#define TXB0SIDH 0x31
// -- Masks underneith

// TRANSMIT BUFFER 1 STANDARD IDENTIFIER HIGH
#define TXB1SIDH 0x41
// -- Masks underneith

// TRANSMIT BUFFER 2 STANDARD IDENTIFIER HIGH
#define TXB2SIDH 0x51
// -- Masks underneith

// TRANSMIT BUFFER 0 STANDARD IDENTIFIER LOW
#define TXB0SIDL 0x32
#define TXB0SIDL_Mask_EXIDE 0x08
#define TXB0SIDL_Mask_TXB0SIDL_EID 0x07
#define TXB0SIDL_Mask_TXB0SIDL_SID 0xE0

// TRANSMIT BUFFER 1 STANDARD IDENTIFIER LOW
#define TXB1SIDL 0x42
#define TXB1SIDL_Mask_EXIDE 0x08
#define TXB1SIDL_Mask_TXB1SIDL_EID 0x07
#define TXB1SIDL_Mask_TXB1SIDL_SID 0xE0

// TRANSMIT BUFFER 2 STANDARD IDENTIFIER LOW
#define TXB2SIDL 0x52
#define TXB2SIDL_Mask_EXIDE 0x08
#define TXB2SIDL_Mask_TXB2SIDL_EID 0x07
#define TXB2SIDL_Mask_TXB2SIDL_SID 0xE0

// TRANSMIT BUFFER 0 EXTENDED IDENTIFIER HIGH
#define TXB0EID8 0x33
// -- Masks underneith

// TRANSMIT BUFFER 1 EXTENDED IDENTIFIER HIGH
#define TXB1EID8 0x43
// -- Masks underneith

// TRANSMIT BUFFER 2 EXTENDED IDENTIFIER HIGH
#define TXB2EID8 0x53
// -- Masks underneith

// TRANSMIT BUFFER 0 EXTENDED IDENTIFIER LOW
#define TXB0EID0 0x34
// -- Masks underneith

// TRANSMIT BUFFER 0 EXTENDED IDENTIFIER LOW
#define TXB1EID0 0x44
// -- Masks underneith

// TRANSMIT BUFFER 0 EXTENDED IDENTIFIER LOW
#define TXB2EID0 0x54
// -- Masks underneith

// TRANSMIT BUFFER 0 DATA LENGTH CODE
#define TXB0DLC 0x35
#define TXB0DLC_Mask_RTR 0x20
#define TXB0DLC_Mask_DLC 0x0F

// TRANSMIT BUFFER 1 DATA LENGTH CODE
#define TXB1DLC 0x45
#define TXB1DLC_Mask_RTR 0x20
#define TXB1DLC_Mask_DLC 0x0F

// TRANSMIT BUFFER 2 DATA LENGTH CODE
#define TXB2DLC 0x55
#define TXB2DLC_Mask_RTR 0x20
#define TXB2DLC_Mask_DLC 0x0F

// Data

// TX0 Data
#define TXB0D0 0x36
#define TXB0D1 0x37
#define TXB0D2 0x38
#define TXB0D3 0x39
#define TXB0D4 0x3A
#define TXB0D5 0x3B
#define TXB0D6 0x3C
#define TXB0D7 0x3D

// TX1 Data
#define TXB1D0 0x46
#define TXB1D1 0x47
#define TXB1D2 0x48
#define TXB1D3 0x49
#define TXB1D4 0x4A
#define TXB1D5 0x4B
#define TXB1D6 0x4C
#define TXB1D7 0x4D

// TX2 Data
#define TXB2D0 0x56
#define TXB2D1 0x57
#define TXB2D2 0x58
#define TXB2D3 0x59
#define TXB2D4 0x5A
#define TXB2D5 0x5B
#define TXB2D6 0x5C
#define TXB2D7 0x5D



// RX REGISTERS
//-----------------------------------------------------------------//

// RECEIVE BUFFER 0 CONTROL
#define RXB0CTRL 0x60
#define RXB0CTRL_Mask_RXM 0x60 // Opperation Mode Bits

// RECEIVE BUFFER 1 CONTROL
#define RXB1CTRL 0x70
#define RXB1CTRL_Mask_RXM 0x60 // Opperation Mode Bits

// RXnBF PIN CONTROL AND STATUS
#define BFPCTRL 0x0C
// -- Masks -- //

// RECEIVE BUFFER 0 STANDARD IDENTIFIER HIGH
#define RXB0SIDH 0x61
// -- Masks -- //

// RECEIVE BUFFER 1 STANDARD IDENTIFIER HIGH
#define RXB1SIDH 0x71
// -- Masks -- //

// RECEIVE BUFFER 0 STANDARD IDENTIFIER LOW
#define RXB0SIDL 0x62
#define RXB0SIDL_Mask_IDE 0x08

// RECEIVE BUFFER 1 STANDARD IDENTIFIER LOW
#define RXB1SIDL 0x72
#define RXB1SIDL_Mask_IDE 0x08

// RECEIVE BUFFER 0 EXTENDED IDENTIFIER HIGH
#define RXB0EID8 0x63
// -- Masks -- //

// RECEIVE BUFFER 1 EXTENDED IDENTIFIER HIGH
#define RXB1EID8 0x73
// -- Masks -- //

// RECEIVE BUFFER 0 EXTENDED IDENTIFIER LOW
#define RXB0EID0 0x64
// -- Masks -- //

// RECEIVE BUFFER 0 EXTENDED IDENTIFIER LOW
#define RXB1EID0 0x74
// -- Masks -- //

// RECEIVE BUFFER 0 DATA LENGTH CODE
#define RXB0DLC 0x65
// -- Masks -- //

// RECEIVE BUFFER 1 DATA LENGTH CODE
#define RXB1DLC 0x75
// -- Masks -- //

// RECEIVE BUFFER 0 DATA
#define RXB0D0 0x66
#define RXB0D1 0x67
#define RXB0D2 0x68
#define RXB0D3 0x69
#define RXB0D4 0x6A
#define RXB0D5 0x6B
#define RXB0D6 0x6C
#define RXB0D7 0x6D

// RECEIVE BUFFER 1 DATA
#define RXB1D0 0x76
#define RXB1D1 0x77
#define RXB1D2 0x78
#define RXB1D3 0x79
#define RXB1D4 0x7A
#define RXB1D5 0x7B
#define RXB1D6 0x7C
#define RXB1D7 0x7D


// BIT TIMING REGISTERS
//-----------------------------------------------------------------//

// CONFIGURATION 1
#define CNF1 0x2A
#define CNF1_Mask_BRP 0x3F
#define CNF1_Mask_SJW 0xC0

// CONFIGURATION 2
#define CNF2 0x29
#define CNF2_Mask_BTLMODE 0x80 // PS2 Mode bit
#define CNF2_Mask_SAM 0x40 // Sample point config bit
#define CNF2_Mask_PHSEG1 0x38 // PS1 length bits
#define CNF2_Mask_PRSEG 0x07 // propigation segment length bits

// CONFIGURATION 3
#define CNF3 0x28
#define CNF3_Mask_PHSEG2 0x07 // ps2 length bits
#define CNF3_Mask_SOF 0x80 // start of frame pin enable bit
#define CNF3_Mask_WAKFIL 0x40 // wake up filter mode bit


// ERROR COUNTING REGISTERS
//-----------------------------------------------------------------//

// TRANSMIT ERROR COUNTER
#define TEC 0x1C

// RECEIVER ERROR COUNTER
#define REC 0x1D

// ERROR FLAG
#define EFLG 0x2D
// -- Masks -- //



// INTERUPT REGISTERS
//-----------------------------------------------------------------//

// INTERRUPT ENABLE
#define CANINTE 0x2B
// -- Masks -- //

// INTERRUPT FLAG
#define CANINTF 0x2C
#define CANINTF_Mask_RX0IF 0x01
#define CANINTF_Mask_RX1IF 0x02
#define CANINTF_Mask_MERRF 0x80
#define CANINTF_Mask_TX0IF 0x04
#define CANINTF_Mask_TX1IF 0x08
#define CANINTF_Mask_TX2IF 0x10


// MODES OF OPPERATION
//-----------------------------------------------------------------//

// XF // CAN CONTROL REGISTER
#define CANCTRL 0x0F
#define CANCTRL_Mask_REQOP 0xE0 // set opperation mode
#define CANCTRL_Mask_CLKPRE 0x03 // clock pin pre-scaler
#define CANCTRL_Mask_CLKEN 0x04 // clockout pin enable bit
#define CANCTRL_Mask_OSM 0x08 // TX one shot mode

// XE // CAN STATUS REGISTER
#define CANSTAT 0x0E
// -- Masks -- //

// END OF DEFINTIONS
#endif
