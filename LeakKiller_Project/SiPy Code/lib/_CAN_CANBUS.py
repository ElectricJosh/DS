from _CAN_mcp2515 import MCP2515Backend
from _CAN_mcp2515_registers import MCP2515_Reg

class CAN_M:
    ID = 0
    Length = 0

    Data_0 = 0 # immutable in an array otherwise
    Data_1 = 0
    Data_2 = 0
    Data_3 = 0
    Data_4 = 0
    Data_5 = 0
    Data_6 = 0
    Data_7 = 0

    def __init__(self): # kind of redundant
        ID = 0 
        Length = 0

        Data_0 = 0
        Data_1 = 0
        Data_2 = 0
        Data_3 = 0
        Data_4 = 0
        Data_5 = 0
        Data_6 = 0
        Data_7 = 0

class CAN_Backend: # MCP2515 running 8MHz clock, 0 scaling = 500kbps bus speed
    mcp2515_Instance = 0

    def __init__(self, ScalingFactor, SPI_Object, CS_Object): 
        self.mcp2515_Instance = MCP2515Backend(SPI_Object, CS_Object) 

        SyncJumpWidthValue = 0 << 6
        PS2ModeValue = 1 << 7
        SamplePointConfigValue = 0 << 6
        StartOfFrameModeValue = 1 << 7
        WakeUpFilterBitValue = 0 << 6

        # 16MHz = 15 + 1 bits wide
        # 8MHz = 4 + 1 bits wide
        
        PS1TimeValue = 1 << 3
        PS2TimeValue = 2 << 0
        PropagationSegmentValue = 1 << 0

        #

        NormalOpperationModeValue = 0 << 5
        ConfigOpperationModeValue = 4 << 5
        ListenOpperationModeValue = 3 << 5

        ClkOutPinPrescaleValue = 0 << 0
        ClkOutPinEnableValue = 0 << 2

        RXB0OpperationModeValue = 0 << 5
        RXB1OpperationModeValue = 0 << 5

        
        #  // Configurating CAN bitrate
        self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.CANCTRL, MCP2515_Reg.CANCTRL_Mask_REQOP, ConfigOpperationModeValue)

        #  // CONFIG1 // CHECKED REGISTER AND CORRECT
        self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.CNF1, MCP2515_Reg.CNF1_Mask_BRP, ScalingFactor)
        self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.CNF1, MCP2515_Reg.CNF1_Mask_SJW, SyncJumpWidthValue)

        #  // CONFIG2 // CHECKED REGISTER AND CORRECT
        self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.CNF2, MCP2515_Reg.CNF2_Mask_BTLMODE, PS2ModeValue) 
        self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.CNF2, MCP2515_Reg.CNF2_Mask_SAM, SamplePointConfigValue)
        self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.CNF2, MCP2515_Reg.CNF2_Mask_PHSEG1, PS1TimeValue)
        self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.CNF2, MCP2515_Reg.CNF2_Mask_PRSEG, PropagationSegmentValue)

        #  // CONFIG3 // CHECKED REGISTER AND CORRECT
        self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.CNF3, MCP2515_Reg.CNF3_Mask_SOF, StartOfFrameModeValue)
        self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.CNF3, MCP2515_Reg.CNF3_Mask_WAKFIL, WakeUpFilterBitValue)
        self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.CNF3, MCP2515_Reg.CNF3_Mask_PHSEG2, PS2TimeValue)

        #  // CANCTRL
        self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.CANCTRL, MCP2515_Reg.CANCTRL_Mask_CLKPRE, ClkOutPinPrescaleValue)
        self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.CANCTRL, MCP2515_Reg.CANCTRL_Mask_CLKEN, ClkOutPinEnableValue)
        self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.CANCTRL, MCP2515_Reg.CANCTRL_Mask_OSM, 255)

        #  // RXB CTRL
        self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.RXB0CTRL, MCP2515_Reg.RXB0CTRL_Mask_RXM, RXB0OpperationModeValue)
        self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.RXB1CTRL, MCP2515_Reg.RXB1CTRL_Mask_RXM, RXB1OpperationModeValue)

        self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.CANCTRL, MCP2515_Reg.CANCTRL_Mask_OSM, 255)

        self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.CANCTRL, MCP2515_Reg.CANCTRL_Mask_REQOP, NormalOpperationModeValue)
        
    # -----------------------------------------------------
    # CAN Get Message
    # -----------------------------------------------------

    def Get_Message(self, CAN_Message):

        CheckFlags = self.mcp2515_Instance.MCP2515_Read(MCP2515_Reg.CANINTF) 
        if((CheckFlags & MCP2515_Reg.CANINTF_Mask_RX0IF) > 0):
            StandardLow = self.mcp2515_Instance.MCP2515_Read(MCP2515_Reg.RXB0SIDL) 
            StandardHigh = self.mcp2515_Instance.MCP2515_Read(MCP2515_Reg.RXB0SIDH)
            ExtendedLow = self.mcp2515_Instance.MCP2515_Read(MCP2515_Reg.RXB0EID0) 
            ExtendedMid = self.mcp2515_Instance.MCP2515_Read(MCP2515_Reg.RXB0EID8) 
            ExtendedHigh = (StandardLow & 0x03) 

            CAN_Message.Length = self.mcp2515_Instance.MCP2515_Read(MCP2515_Reg.RXB0DLC)
            ID = 0

            if((StandardLow & MCP2515_Reg.RXB0SIDL_Mask_IDE) == 0):
                ID |= (StandardLow >> 5)
                ID |= (StandardHigh << 3)
            else:
                ID |= (ExtendedLow)
                ID |= (ExtendedMid << 8)
                ID |= (ExtendedHigh <<18)
                ID |= ((StandardLow>>5)<<21)
                ID |= (StandardHigh<<24)

            CAN_Message.ID = ID
            CAN_Message.Data_0 = self.mcp2515_Instance.MCP2515_Read(MCP2515_Reg.RXB0D0) 
            CAN_Message.Data_1 = self.mcp2515_Instance.MCP2515_Read(MCP2515_Reg.RXB0D1) 
            CAN_Message.Data_2 = self.mcp2515_Instance.MCP2515_Read(MCP2515_Reg.RXB0D2) 
            CAN_Message.Data_3 = self.mcp2515_Instance.MCP2515_Read(MCP2515_Reg.RXB0D3) 
            CAN_Message.Data_4 = self.mcp2515_Instance.MCP2515_Read(MCP2515_Reg.RXB0D4) 
            CAN_Message.Data_5 = self.mcp2515_Instance.MCP2515_Read(MCP2515_Reg.RXB0D5) 
            CAN_Message.Data_6 = self.mcp2515_Instance.MCP2515_Read(MCP2515_Reg.RXB0D6)
            CAN_Message.Data_7 = self.mcp2515_Instance.MCP2515_Read(MCP2515_Reg.RXB0D7)

            self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.CANINTF, MCP2515_Reg.CANINTF_Mask_RX0IF, 0)

            return True

        if((CheckFlags & MCP2515_Reg.CANINTF_Mask_RX1IF) > 0):

            StandardLow = self.mcp2515_Instance.MCP2515_Read(MCP2515_Reg.RXB1SIDL) 
            StandardHigh = self.mcp2515_Instance.MCP2515_Read(MCP2515_Reg.RXB1SIDH) 
            ExtendedLow = self.mcp2515_Instance.MCP2515_Read(MCP2515_Reg.RXB1EID0) 
            ExtendedMid = self.mcp2515_Instance.MCP2515_Read(MCP2515_Reg.RXB1EID8) 
            ExtendedHigh = (StandardLow & 0x03)

            CAN_Message.Length = self.mcp2515_Instance.MCP2515_Read(MCP2515_Reg.RXB1DLC)

            ID = 0
            if((StandardLow & MCP2515_Reg.RXB1SIDL_Mask_IDE) == 0):
                ID |= (StandardLow >> 5)
                ID |= (StandardHigh << 3)
            else: # extended
                ID |= (ExtendedLow)
                ID |= (ExtendedMid << 8)
                ID |= (ExtendedHigh <<18)
                ID |= (StandardLow>>5)<<21;
                ID |= (StandardHigh<<24)
            CAN_Message.ID = ID

            CAN_Message.Data_0 = self.mcp2515_Instance.MCP2515_Read(MCP2515_Reg.RXB1D0)
            CAN_Message.Data_1 = self.mcp2515_Instance.MCP2515_Read(MCP2515_Reg.RXB1D1)
            CAN_Message.Data_2 = self.mcp2515_Instance.MCP2515_Read(MCP2515_Reg.RXB1D2)
            CAN_Message.Data_3 = self.mcp2515_Instance.MCP2515_Read(MCP2515_Reg.RXB1D3)
            CAN_Message.Data_4 = self.mcp2515_Instance.MCP2515_Read(MCP2515_Reg.RXB1D4)
            CAN_Message.Data_5 = self.mcp2515_Instance.MCP2515_Read(MCP2515_Reg.RXB1D5)
            CAN_Message.Data_6 = self.mcp2515_Instance.MCP2515_Read(MCP2515_Reg.RXB1D6)
            CAN_Message.Data_7 = self.mcp2515_Instance.MCP2515_Read(MCP2515_Reg.RXB1D7)

            self.mcp2515_Instance.Bit_Modify(MCP2515_Reg.CANINTF, MCP2515_Reg.CANINTF_Mask_RX1IF, 0)

            return True
    
        return False

    # -----------------------------------------------------
    # CAN Send Message
    # -----------------------------------------------------

    def Send_Message(self, CAN_Message, ExtendedFlag):
        self.mcp2515_Instance.MCP2515_Write(MCP2515_Reg.CANINTF, 0x00)
        CheckFlags = self.mcp2515_Instance.MCP2515_Read(MCP2515_Reg.CANINTF) 
        if((CheckFlags & MCP2515_Reg.CANINTF_Mask_TX0IF) == 0):
            if(ExtendedFlag):
                self.mcp2515_Instance.Bit_Modify(MCP2515_Reg.TXB0SIDL, MCP2515_Reg.TXB0SIDL_Mask_EXIDE, 255)
                CAN_Message.ID &= 0x1FFFFFFF
                #      // Extended registers
                E_Bot = byte(CAN_Message.ID & 0xFF) 
                E_Mid = byte((CAN_Message.ID & 0xFF00) >> 8) 
                E_Top = byte((CAN_Message.ID & 0x030000) >> 16) 

                #      // Standard registers
                S_Bot = byte((CAN_Message.ID & 0x1C0000) >> 13) 
                S_Top = byte((CAN_Message.ID & 0x1FE00000) >> 21)

                #      // Write
                self.mcp2515_Instance.Write(MCP2515_Reg.TXB0EID0, E_Bot)
                self.mcp2515_Instance.Write(MCP2515_Reg.TXB0EID8, E_Mid)
                self.mcp2515_Instance.Bit_Modify(MCP2515_Reg.TXB0SIDL, MCP2515_Reg.TXB0SIDL_Mask_TXB0SIDL_EID, E_Top)
                self.mcp2515_Instance.Bit_Modify(MCP2515_Reg.TXB0SIDL, MCP2515_Reg.TXB0SIDL_Mask_TXB0SIDL_SID, S_Bot) 
                self.mcp2515_Instance.MCP2515_Write(MCP2515_Reg.TXB0SIDH, S_Top) 
            else: # Standard 11 bit ID
                self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.TXB0SIDL, MCP2515_Reg.TXB0SIDL_Mask_EXIDE, 0) 
                ID_Masked = (CAN_Message.ID & 0x07FF) 
                ID_Upper = (ID_Masked >> 3) 
                ID_Lower = ((CAN_Message.ID & 0x07) << 5) 
                self.mcp2515_Instance.MCP2515_Write(MCP2515_Reg.TXB0SIDH, ID_Upper) 
                self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.TXB0SIDL, MCP2515_Reg.TXB0SIDL_Mask_TXB0SIDL_SID, ID_Lower)
        
            self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.TXB0DLC, MCP2515_Reg.TXB0DLC_Mask_RTR, 0)

            CAN_Message.Length &= 0x0F
            self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.TXB0DLC, MCP2515_Reg.TXB0DLC_Mask_DLC, CAN_Message.Length)

            self.mcp2515_Instance.MCP2515_Write(MCP2515_Reg.TXB0D0, CAN_Message.Data_0)
            self.mcp2515_Instance.MCP2515_Write(MCP2515_Reg.TXB0D1, CAN_Message.Data_1) 
            self.mcp2515_Instance.MCP2515_Write(MCP2515_Reg.TXB0D2, CAN_Message.Data_2) 
            self.mcp2515_Instance.MCP2515_Write(MCP2515_Reg.TXB0D3, CAN_Message.Data_3) 
            self.mcp2515_Instance.MCP2515_Write(MCP2515_Reg.TXB0D4, CAN_Message.Data_4) 
            self.mcp2515_Instance.MCP2515_Write(MCP2515_Reg.TXB0D5, CAN_Message.Data_5) 
            self.mcp2515_Instance.MCP2515_Write(MCP2515_Reg.TXB0D6, CAN_Message.Data_6)
            self.mcp2515_Instance.MCP2515_Write(MCP2515_Reg.TXB0D7, CAN_Message.Data_7)

            self.mcp2515_Instance.MCP2515_TX_Request_To_Send(True, False, False)
        elif((CheckFlags & MCP2515_Reg.CANINTF_Mask_TX1IF) == 0):
            if(ExtendedFlag):
                self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.TXB1SIDL, MCP2515_Reg.TXB1SIDL_Mask_EXIDE, 255)
                CAN_Message.ID &= 0x1FFFFFFF 

                #      // Extended registers
                E_Bot = CAN_Message.ID & 0xFF 
                E_Mid = (CAN_Message.ID & 0xFF00) >> 8 
                E_Top = (CAN_Message.ID & 0x030000) >> 16 

                #      // Standard registers
                S_Bot = (CAN_Message.ID & 0x1C0000) >> 13 
                S_Top = (CAN_Message.ID & 0x1FE00000) >> 21 

                #      // Write
                self.mcp2515_Instance.Write(MCP2515_Reg.TXB1EID0, E_Bot) 
                self.mcp2515_Instance.Write(MCP2515_Reg.TXB1EID8, E_Mid) 
                self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.TXB1SIDL, MCP2515_Reg.TXB1SIDL_Mask_TXB1SIDL_EID, E_Top)
                self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.TXB1SIDL, MCP2515_Reg.TXB1SIDL_Mask_TXB1SIDL_SID, S_Bot)
                self.mcp2515_Instance.Write(MCP2515_Reg.TXB1SIDH, S_Top)
        
            else: #    else // Standard 11 bit ID
                self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.TXB1SIDL, MCP2515_Reg.TXB1SIDL_Mask_EXIDE, 0) 
                ID_Masked = CAN_Message.ID & 0x07FF 
                ID_Upper = ID_Masked >> 3
                ID_Lower = (CAN_Message.ID & 0x07) << 5 
                self.mcp2515_Instance.Write(MCP2515_Reg.TXB1SIDH, ID_Upper) 
                self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.TXB1SIDL, MCP2515_Reg.TXB1SIDL_Mask_TXB1SIDL_SID, ID_Lower)
        
                self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.TXB1DLC, MCP2515_Reg.TXB1DLC_Mask_RTR, 0)
                CAN_Message.Length &= 0x0F
                self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.TXB1DLC, MCP2515_Reg.TXB1DLC_Mask_DLC, CAN_Message.Length)

            self.mcp2515_Instance.Write(MCP2515_Reg.TXB1D0, CAN_Message.Data[0]) 
            self.mcp2515_Instance.Write(MCP2515_Reg.TXB1D1, CAN_Message.Data[1])
            self.mcp2515_Instance.Write(MCP2515_Reg.TXB1D2, CAN_Message.Data[2])
            self.mcp2515_Instance.Write(MCP2515_Reg.TXB1D3, CAN_Message.Data[3])
            self.mcp2515_Instance.Write(MCP2515_Reg.TXB1D4, CAN_Message.Data[4])
            self.mcp2515_Instance.Write(MCP2515_Reg.TXB1D5, CAN_Message.Data[5])
            self.mcp2515_Instance.Write(MCP2515_Reg.TXB1D6, CAN_Message.Data[6])
            self.mcp2515_Instance.Write(MCP2515_Reg.TXB1D7, CAN_Message.Data[7])

            self.mcp2515_Instance.TX_Request_To_Send(False, True, False )
        elif((CheckFlags & MCP2515_Reg.CANINTF_Mask_TX2IF) == 0):
            if(ExtendedFlag):
                self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.TXB2SIDL, MCP2515_Reg.TXB2SIDL_Mask_EXIDE, 255) 
                CAN_Message.ID &= 0x1FFFFFFF

                #      // Extended registers
                E_Bot = CAN_Message.ID & 0xFF
                E_Mid = (CAN_Message.ID & 0xFF00) >> 8
                E_Top = (CAN_Message.ID & 0x030000) >> 16

                #      // Standard registers
                S_Bot = (CAN_Message.ID & 0x1C0000) >> 13 
                S_Top = (CAN_Message.ID & 0x1FE00000) >> 21
            
                #      // Write
                self.mcp2515_Instance.Write(MCP2515_Reg.TXB2EID0, E_Bot)
                self.mcp2515_Instance.Write (MCP2515_Reg.TXB2EID8, E_Mid)
                self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.TXB2SIDL, MCP2515_Reg.TXB2SIDL_Mask_TXB2SIDL_EID, E_Top)
                self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.TXB2SIDL, MCP2515_Reg.TXB2SIDL_Mask_TXB2SIDL_SID, S_Bot)
                self.mcp2515_Instance.Write(MCP2515_Reg.TXB2SIDH, S_Top)
            else: 
                self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.TXB2SIDL, MCP2515_Reg.TXB2SIDL_Mask_EXIDE, 0) 
                ID_Masked = CAN_Message.ID & 0x07FF 
                ID_Upper = ID_Masked >> 3 
                ID_Lower = (CAN_Message.ID & 0x07) << 5 
                self.mcp2515_Instance.Write(MCP2515_Reg.TXB2SIDH, ID_Upper)
                self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.TXB2SIDL, MCP2515_Reg.TXB2SIDL_Mask_TXB2SIDL_SID, ID_Lower)
        
            self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.TXB2DLC, MCP2515_Reg.TXB2DLC_Mask_RTR, 0)

            CAN_Message.Length &= 0x0F
            self.mcp2515_Instance.MCP2515_Bit_Modify(MCP2515_Reg.TXB2DLC, MCP2515_Reg.TXB2DLC_Mask_DLC, CAN_Message.Length)

            self.mcp2515_Instance.Write(MCP2515_Reg.TXB2D0, CAN_Message.Data[0])
            self.mcp2515_Instance.Write(MCP2515_Reg.TXB2D1, CAN_Message.Data[1])
            self.mcp2515_Instance.Write(MCP2515_Reg.TXB2D2, CAN_Message.Data[2])
            self.mcp2515_Instance.Write(MCP2515_Reg.TXB2D3, CAN_Message.Data[3])
            self.mcp2515_Instance.Write(MCP2515_Reg.TXB2D4, CAN_Message.Data[4])
            self.mcp2515_Instance.Write(MCP2515_Reg.TXB2D5, CAN_Message.Data[5])
            self.mcp2515_Instance.Write(MCP2515_Reg.TXB2D6, CAN_Message.Data[6])
            self.mcp2515_Instance.Write(MCP2515_Reg.TXB2D7, CAN_Message.Data[7])

            self.mcp2515_Instance.TX_Request_To_Send(False, False, True)