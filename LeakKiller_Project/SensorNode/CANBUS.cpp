#include "CANBUS.h"

// -----------------------------------------------------
// CAN Constructor
// -----------------------------------------------------

CAN::CAN()
{

}

// -----------------------------------------------------
// CAN Initialise
// -----------------------------------------------------

void CAN::Initialise(byte ScalingFactor)  // TQ = 2 x (BRP + 1)/FOSC // scaling factor will add one and be multiplied by two
{
  mcp2515::Initialise();

  // shifted << to allign to the respective offsets in the registers.

  // Sync controller variables
  //Scaling Factor Register checked and writes properly
  byte SyncJumpWidthValue = 0 << 6; // register checked works properly
  byte PS2ModeValue = 1 << 7; // mode 1 so the length is controlled by config3 register
  byte SamplePointConfigValue = 0 << 6;
  byte StartOfFrameModeValue = 1 << 7;
  byte WakeUpFilterBitValue = 0 << 6; // disabled

  // Baud rate time control variables 15 + 1 sync bit = 16 -> 1Mhz / 2 (min pre-scaler value) = 500kbps
  byte PS1TimeValue = 1 << 3; // writes correctly // 16Mhz = 5 // 8Mhz = 
  byte PS2TimeValue = 2 << 0; // writes correctly // 16Mhz = 5 // 8Mhz =
  byte PropagationSegmentValue = 1 << 0; // writes correctly // 16 Mhz = 5 // 8Mhz = 
  // remember there is a sync bit of 1

  byte NormalOpperationModeValue = 0 << 5; // Normal Mode
  byte ConfigOpperationModeValue = 4 << 5; // Config Mode
  byte ListenOpperationModeValue = 3 << 5; // Listen Only Mode

  byte ClkOutPinPrescaleValue = 0 << 0;
  byte ClkOutPinEnableValue = 0 << 2;

  byte RXB0OpperationModeValue = 0 << 5;
  byte RXB1OpperationModeValue = 0 << 5;



  // Configurating CAN bitrate
  mcp2515::Bit_Modify(CANCTRL, CANCTRL_Mask_REQOP, ConfigOpperationModeValue); // set to config opperation mode

  // CONFIG1 // CHECKED REGISTER AND CORRECT
  mcp2515::Bit_Modify(CNF1, CNF1_Mask_BRP, ScalingFactor);
  mcp2515::Bit_Modify(CNF1, CNF1_Mask_SJW, SyncJumpWidthValue); // 1 = 2TQ

  // CONFIG2 // CHECKED REGISTER AND CORRECT
  mcp2515::Bit_Modify(CNF2, CNF2_Mask_BTLMODE, PS2ModeValue);
  mcp2515::Bit_Modify(CNF2, CNF2_Mask_SAM, SamplePointConfigValue);
  mcp2515::Bit_Modify(CNF2, CNF2_Mask_PHSEG1, PS1TimeValue);
  mcp2515::Bit_Modify(CNF2, CNF2_Mask_PRSEG, PropagationSegmentValue);

  // CONFIG3 // CHECKED REGISTER AND CORRECT
  mcp2515::Bit_Modify(CNF3, CNF3_Mask_SOF, StartOfFrameModeValue);
  mcp2515::Bit_Modify(CNF3, CNF3_Mask_WAKFIL, WakeUpFilterBitValue);
  mcp2515::Bit_Modify(CNF3, CNF3_Mask_PHSEG2, PS2TimeValue);

  // CANCTRL
  mcp2515::Bit_Modify(CANCTRL, CANCTRL_Mask_CLKPRE, ClkOutPinPrescaleValue); // <-- probably delete any unnessacary register allocations now that I have debugged everything.
  mcp2515::Bit_Modify(CANCTRL, CANCTRL_Mask_CLKEN, ClkOutPinEnableValue);
  mcp2515::Bit_Modify(CANCTRL, CANCTRL_Mask_OSM, 255); // One shot mode enable = 1 .. <<<---------------------------

  // RXB CTRL
  mcp2515::Bit_Modify(RXB0CTRL, RXB0CTRL_Mask_RXM, RXB0OpperationModeValue);
  mcp2515::Bit_Modify(RXB1CTRL, RXB1CTRL_Mask_RXM, RXB1OpperationModeValue);

  // turn off rollover on RX buffers

  // have one shot mode here but commented out
  mcp2515::Bit_Modify(CANCTRL, CANCTRL_Mask_OSM, 255); // One shot mode

  mcp2515::Bit_Modify(CANCTRL, CANCTRL_Mask_REQOP, NormalOpperationModeValue);
}

// -----------------------------------------------------
// CAN Get Message
// -----------------------------------------------------

// https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.cbclx01/cplr233.htm
// Send by reference.

bool CAN::Get_Message(CAN_M *M) // return message by reference. // bool will flag if a message was recieved or not.
{
  byte CheckFlags = mcp2515::Read(CANINTF); // getting flags

  if ((CheckFlags & CANINTF_Mask_RX0IF) > 0) // masks the register to see if the individual bit is set.
  {
    unsigned long StandardLow = mcp2515::Read(RXB0SIDL);
    unsigned long StandardHigh = mcp2515::Read(RXB0SIDH);
    unsigned long ExtendedLow = mcp2515::Read(RXB0EID0);
    unsigned long ExtendedMid = mcp2515::Read(RXB0EID8);
    unsigned long ExtendedHigh = (StandardLow & 0x03);

    M->Length = mcp2515::Read(RXB0DLC);

    unsigned long ID = 0;
    if ((StandardLow & RXB0SIDL_Mask_IDE) == 0) // standard
    {
      ID |= (StandardLow >> 5);
      ID |= (StandardHigh << 3);
    }
    else // extended
    {
      // Standard high, Standard low, EX High, EX mid, EX low
      ID |= (ExtendedLow);
      ID |= (ExtendedMid << 8);
      ID |= (ExtendedHigh <<18);
      ID |= (StandardLow>>5)<<21; // leave this
      ID |= (StandardHigh<<24);
    }
    M->ID = ID;

    M->Data[0] = mcp2515::Read(RXB0D0);
    M->Data[1] = mcp2515::Read(RXB0D1);
    M->Data[2] = mcp2515::Read(RXB0D2);
    M->Data[3] = mcp2515::Read(RXB0D3);
    M->Data[4] = mcp2515::Read(RXB0D4);
    M->Data[5] = mcp2515::Read(RXB0D5);
    M->Data[6] = mcp2515::Read(RXB0D6);
    M->Data[7] = mcp2515::Read(RXB0D7);

    mcp2515::Bit_Modify(CANINTF, CANINTF_Mask_RX0IF, 0); // reset RX flag on MCP2515

    return HIGH;
  }
  if ((CheckFlags & CANINTF_Mask_RX1IF) > 0) // masks the register to see if the individual bit is set.
  {
    unsigned long StandardLow = mcp2515::Read(RXB1SIDL);
    unsigned long StandardHigh = mcp2515::Read(RXB1SIDH);
    unsigned long ExtendedLow = mcp2515::Read(RXB1EID0);
    unsigned long ExtendedMid = mcp2515::Read(RXB1EID8);
    unsigned long ExtendedHigh = (StandardLow & 0x03);

    M->Length = mcp2515::Read(RXB1DLC);

    unsigned long ID = 0;
    if ((StandardLow & RXB1SIDL_Mask_IDE) == 0) // standard
    {
      ID |= (StandardLow >> 5);
      ID |= (StandardHigh << 3);
    }
    else // extended
    {
      // Standard high, Standard low, EX High, EX mid, EX low
      ID |= (ExtendedLow);
      ID |= (ExtendedMid << 8);
      ID |= (ExtendedHigh <<18);
      ID |= (StandardLow>>5)<<21; // leave this
      ID |= (StandardHigh<<24);
    }
    M->ID = ID;

    M->Data[0] = mcp2515::Read(RXB1D0);
    M->Data[1] = mcp2515::Read(RXB1D1);
    M->Data[2] = mcp2515::Read(RXB1D2);
    M->Data[3] = mcp2515::Read(RXB1D3);
    M->Data[4] = mcp2515::Read(RXB1D4);
    M->Data[5] = mcp2515::Read(RXB1D5);
    M->Data[6] = mcp2515::Read(RXB1D6);
    M->Data[7] = mcp2515::Read(RXB1D7);

    mcp2515::Bit_Modify(CANINTF, CANINTF_Mask_RX1IF, 0); // reset RX flag on MCP2515

    return HIGH;

  }

  return LOW;
}

// -----------------------------------------------------
// CAN Send Message
// -----------------------------------------------------

// Standard frame uses 11 bit ID extended frame uses and extra 18 bits in the EID registers to give a total of 29 bit identifier.
// lower addresses have priority
// it is extained on pg.7 of the datasheet
// with the standard frame you simple take the bottom 11 bits of the total 29 bits
// with the extended frame the standard registers take the top 11 bits and the rest is put in the extended.

// Add message length, RTR and data

void CAN::Send_Message(CAN_M *M, bool ExtendedFlag)
{
  mcp2515::Write(CANINTF, 0x00); // this fixes it
  byte CheckFlags = mcp2515::Read(CANINTF); // Holds the TX flags // bit 2,3,4

  if ((CheckFlags & CANINTF_Mask_TX0IF) == 0) // no pending transmission
  {
    if (ExtendedFlag) // extended ID // 16 bit ID
    {
      mcp2515::Bit_Modify(TXB0SIDL, TXB0SIDL_Mask_EXIDE, 255); // sets the TX buffer to use the extended message register.
      M->ID &= 0x1FFFFFFF; // Masking 29 bits

      // Extended registers
      byte E_Bot = byte(M->ID & 0xFF); // TXB0EID0
      byte E_Mid = byte((M->ID & 0xFF00) >> 8); // TXB0EID8
      byte E_Top = byte((M->ID & 0x030000) >> 16); // TXB0SIDL // bitmodify

      // Standard registers
      byte S_Bot = byte((M->ID & 0x1C0000) >> 13); // TXB0SIDL // 3 bits // bitmodify
      byte S_Top = byte((M->ID & 0x1FE00000) >> 21); // TXB0SIDH // 8 bits // write

      // Write
      mcp2515::Write(TXB0EID0, E_Bot);
      mcp2515::Write(TXB0EID8, E_Mid);
      mcp2515::Bit_Modify(TXB0SIDL, TXB0SIDL_Mask_TXB0SIDL_EID, E_Top);
      mcp2515::Bit_Modify(TXB0SIDL, TXB0SIDL_Mask_TXB0SIDL_SID, S_Bot);
      mcp2515::Write(TXB0SIDH, S_Top);
    }
    else // Standard 11 bit ID
    {
      mcp2515::Bit_Modify(TXB0SIDL, TXB0SIDL_Mask_EXIDE, 0); // sets the TX buffer to use the standard message register.

      int ID_Masked = M->ID & 0x07FF; // masks the standard 11 bits
      byte ID_Upper = byte(ID_Masked >> 3);
      byte ID_Lower = byte((M->ID & 0x07) << 5); // lower bits are in a weird place in the reg
      mcp2515::Write(TXB0SIDH, ID_Upper);
      mcp2515::Bit_Modify(TXB0SIDL, TXB0SIDL_Mask_TXB0SIDL_SID, ID_Lower);
    }

    mcp2515::Bit_Modify(TXB0DLC, TXB0DLC_Mask_RTR, 0); // Sets the message to data mode

    M->Length &= 0x0F; // Masks the variable to 4 bits
    mcp2515::Bit_Modify(TXB0DLC, TXB0DLC_Mask_DLC, M->Length); // Sets the message to data mode

    mcp2515::Write(TXB0D0, M->Data[0]);
    mcp2515::Write(TXB0D1, M->Data[1]);
    mcp2515::Write(TXB0D2, M->Data[2]);
    mcp2515::Write(TXB0D3, M->Data[3]);
    mcp2515::Write(TXB0D4, M->Data[4]);
    mcp2515::Write(TXB0D5, M->Data[5]);
    mcp2515::Write(TXB0D6, M->Data[6]);
    mcp2515::Write(TXB0D7, M->Data[7]);

    mcp2515::TX_Request_To_Send(HIGH, LOW, LOW); // Set send flag of specific register
  }

  else if ((CheckFlags & CANINTF_Mask_TX1IF) == 0)
  {
    if (ExtendedFlag) // extended ID // 16 bit ID
    {
      mcp2515::Bit_Modify(TXB1SIDL, TXB1SIDL_Mask_EXIDE, 255); // sets the TX buffer to use the extended message register.
      M->ID &= 0x1FFFFFFF; // Masking 29 bits

      // Extended registers
      byte E_Bot = byte(M->ID & 0xFF); // TXB0EID0
      byte E_Mid = byte((M->ID & 0xFF00) >> 8); // TXB0EID8
      byte E_Top = byte((M->ID & 0x030000) >> 16); // TXB0SIDL // bitmodify

      // Standard registers
      byte S_Bot = byte((M->ID & 0x1C0000) >> 13); // TXB0SIDL // 3 bits // bitmodify
      byte S_Top = byte((M->ID & 0x1FE00000) >> 21); // TXB0SIDH // 8 bits // write

      // Write
      mcp2515::Write(TXB1EID0, E_Bot);
      mcp2515::Write(TXB1EID8, E_Mid);
      mcp2515::Bit_Modify(TXB1SIDL, TXB1SIDL_Mask_TXB1SIDL_EID, E_Top);
      mcp2515::Bit_Modify(TXB1SIDL, TXB1SIDL_Mask_TXB1SIDL_SID, S_Bot);
      mcp2515::Write(TXB1SIDH, S_Top);
    }
    else // Standard 11 bit ID
    {
      mcp2515::Bit_Modify(TXB1SIDL, TXB1SIDL_Mask_EXIDE, 0); // sets the TX buffer to use the standard message register.

      int ID_Masked = M->ID & 0x07FF; // masks the standard 11 bits
      byte ID_Upper = byte(ID_Masked >> 3);
      byte ID_Lower = byte((M->ID & 0x07) << 5); // lower bits are in a weird place in the reg
      mcp2515::Write(TXB1SIDH, ID_Upper);
      mcp2515::Bit_Modify(TXB1SIDL, TXB1SIDL_Mask_TXB1SIDL_SID, ID_Lower);
    }

    mcp2515::Bit_Modify(TXB1DLC, TXB1DLC_Mask_RTR, 0); // Sets the message to data mode

    M->Length &= 0x0F; // Masks the variable to 4 bits
    mcp2515::Bit_Modify(TXB1DLC, TXB1DLC_Mask_DLC, M->Length); // Sets the message to data mode

    mcp2515::Write(TXB1D0, M->Data[0]);
    mcp2515::Write(TXB1D1, M->Data[1]);
    mcp2515::Write(TXB1D2, M->Data[2]);
    mcp2515::Write(TXB1D3, M->Data[3]);
    mcp2515::Write(TXB1D4, M->Data[4]);
    mcp2515::Write(TXB1D5, M->Data[5]);
    mcp2515::Write(TXB1D6, M->Data[6]);
    mcp2515::Write(TXB1D7, M->Data[7]);

    mcp2515::TX_Request_To_Send(LOW, HIGH, LOW); // Set send flag of specific register
  }

  else if ((CheckFlags & CANINTF_Mask_TX2IF) == 0)
  {
    if (ExtendedFlag) // extended ID // 16 bit ID
    {
      mcp2515::Bit_Modify(TXB2SIDL, TXB2SIDL_Mask_EXIDE, 255); // sets the TX buffer to use the extended message register.
      M->ID &= 0x1FFFFFFF; // Masking 29 bits

      // Extended registers
      byte E_Bot = byte(M->ID & 0xFF); // TXB0EID0
      byte E_Mid = byte((M->ID & 0xFF00) >> 8); // TXB0EID8
      byte E_Top = byte((M->ID & 0x030000) >> 16); // TXB0SIDL // bitmodify

      // Standard registers
      byte S_Bot = byte((M->ID & 0x1C0000) >> 13); // TXB0SIDL // 3 bits // bitmodify
      byte S_Top = byte((M->ID & 0x1FE00000) >> 21); // TXB0SIDH // 8 bits // write

      // Write
      mcp2515::Write(TXB2EID0, E_Bot);
      mcp2515::Write(TXB2EID8, E_Mid);
      mcp2515::Bit_Modify(TXB2SIDL, TXB2SIDL_Mask_TXB2SIDL_EID, E_Top);
      mcp2515::Bit_Modify(TXB2SIDL, TXB2SIDL_Mask_TXB2SIDL_SID, S_Bot);
      mcp2515::Write(TXB2SIDH, S_Top);
    }
    else // Standard 11 bit ID
    {
      mcp2515::Bit_Modify(TXB2SIDL, TXB2SIDL_Mask_EXIDE, 0); // sets the TX buffer to use the standard message register.

      int ID_Masked = M->ID & 0x07FF; // masks the standard 11 bits
      byte ID_Upper = byte(ID_Masked >> 3);
      byte ID_Lower = byte((M->ID & 0x07) << 5); // lower bits are in a weird place in the reg
      mcp2515::Write(TXB2SIDH, ID_Upper);
      mcp2515::Bit_Modify(TXB2SIDL, TXB2SIDL_Mask_TXB2SIDL_SID, ID_Lower);
    }

    mcp2515::Bit_Modify(TXB2DLC, TXB2DLC_Mask_RTR, 0); // Sets the message to data mode

    M->Length &= 0x0F; // Masks the variable to 4 bits
    mcp2515::Bit_Modify(TXB2DLC, TXB2DLC_Mask_DLC, M->Length); // Sets the message to data mode

    mcp2515::Write(TXB2D0, M->Data[0]);
    mcp2515::Write(TXB2D1, M->Data[1]);
    mcp2515::Write(TXB2D2, M->Data[2]);
    mcp2515::Write(TXB2D3, M->Data[3]);
    mcp2515::Write(TXB2D4, M->Data[4]);
    mcp2515::Write(TXB2D5, M->Data[5]);
    mcp2515::Write(TXB2D6, M->Data[6]);
    mcp2515::Write(TXB2D7, M->Data[7]);

    mcp2515::TX_Request_To_Send(LOW, LOW, HIGH); // Set send flag of specific register
  }
}

