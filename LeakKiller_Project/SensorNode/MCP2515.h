#ifndef mcp2515_h
#define mcp2515_h

#include <Arduino.h> // Includes main arduino API
#include <SPI.h>

#include "ROM_Variables.h"

// MCP2515 Class

class mcp2515
{
  private:

  public:
    mcp2515(void);
    static void Initialise(void);
    static void SPI_CS_Enable(void);
    static void SPI_CS_Disable(void);
    static void Reset(void);
    static byte Read_Status(void);
    static byte Read(byte address);
    static void Write(byte address, byte data);
    static void Bit_Modify(byte address, byte mask, byte data);
    static void TX_Request_To_Send(bool TX1, bool TX2, bool TX3);
    static byte Mask_Finder(byte bit_no);
    static bool Find_Bit(byte x, byte bit_no);
};

#endif
