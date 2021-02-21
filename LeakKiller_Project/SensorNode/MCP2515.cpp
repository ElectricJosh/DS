#include "MCP2515.h"

// -----------------------------------------------------
// mcp2515 Constructor
// -----------------------------------------------------

mcp2515::mcp2515()
{

}

// -----------------------------------------------------
// mcp2515 Initialise
// -----------------------------------------------------

void mcp2515::Initialise()
{
  //
  SPI.begin();
  //SPI.beginTransaction(SPISettings(100,MSBFIRST,SPI_MODE0)); // Start SPI service with default settings
  //SPI.endTransaction();
  //SPI.begin();  
}

// -----------------------------------------------------
// SPI Chip Select Enable
// -----------------------------------------------------

void mcp2515::SPI_CS_Enable()
{
  digitalWrite(SS, LOW);
}

// -----------------------------------------------------
// SPI Chip Select Disable
// -----------------------------------------------------

void mcp2515::SPI_CS_Disable()
{
  digitalWrite(SS, HIGH);
}

// -----------------------------------------------------
// Reset
// -----------------------------------------------------

void mcp2515::Reset()
{
  mcp2515::SPI_CS_Disable();
  mcp2515::SPI_CS_Enable();
  SPI.transfer(RESET);
  mcp2515::SPI_CS_Disable();
}

// -----------------------------------------------------
// Read Status Register // contains the most common status flags for convenience.
// -----------------------------------------------------

byte mcp2515::Read_Status()
{
  mcp2515::SPI_CS_Disable();
  mcp2515::SPI_CS_Enable();
  byte STATUS = 0;
  STATUS = SPI.transfer(READSTATUS);
  STATUS = SPI.transfer(0xFF);
  mcp2515::SPI_CS_Disable();
  return STATUS;
}

// -----------------------------------------------------
// Read Single Register
// -----------------------------------------------------

byte mcp2515::Read(byte address) // this works perfectly
{
  mcp2515::SPI_CS_Disable();
  mcp2515::SPI_CS_Enable();
  SPI.transfer(READ); // instruction
  byte STATUS = 0;
  STATUS = SPI.transfer(address); // address
  STATUS = SPI.transfer(0xFF); // prompt
  mcp2515::SPI_CS_Disable();
  return STATUS;
}

// -----------------------------------------------------
// Write Single Register
// -----------------------------------------------------

void mcp2515::Write(byte address, byte data)
{
  mcp2515::SPI_CS_Disable();
  mcp2515::SPI_CS_Enable();
  SPI.transfer(WRITE);
  SPI.transfer(address);
  SPI.transfer(data);
  mcp2515::SPI_CS_Disable();
}

// -----------------------------------------------------
// Modify a single bit of a single register
// -----------------------------------------------------

void mcp2515::Bit_Modify(byte address, byte mask, byte data) // This works perfectly
{
  mcp2515::SPI_CS_Disable();
  mcp2515::SPI_CS_Enable();
  SPI.transfer(BITMODIFY);
  SPI.transfer(address);
  SPI.transfer(mask);
  SPI.transfer(data);
  mcp2515::SPI_CS_Disable();
}

// -----------------------------------------------------
// Request to send selected tx buffers
// -----------------------------------------------------

void mcp2515::TX_Request_To_Send(bool TX0, bool TX1, bool TX2)
{
  mcp2515::SPI_CS_Disable();
  mcp2515::SPI_CS_Enable();
  byte RTS = REQUESTTOSEND;
  if (TX0)
  {
    RTS = (RTS | mcp2515::Mask_Finder(0));
  }
  if (TX1)
  {
    RTS = (RTS | mcp2515::Mask_Finder(1));
  }
  if (TX2)
  {
    RTS = (RTS | mcp2515::Mask_Finder(2));
  }

  SPI.transfer(RTS);
  mcp2515::SPI_CS_Disable();
}

// -----------------------------------------------------
// Bitwise Mask Finder
// -----------------------------------------------------

byte mcp2515::Mask_Finder(byte bit_no) // Bit number is 0 - 7
{
  return (pow(2, bit_no));
}

// -----------------------------------------------------
// Bitwise Byte Interpreter
// -----------------------------------------------------

bool mcp2515::Find_Bit(byte x, byte bit_no) // Bit number is 0 - 7
{
  byte mask = pow(2, bit_no);
  // 00000001 = 1, 00000010 = 2, 00000100 = 4, 00001000 = 8 etc.

  x = x & mask;
  x = x >> bit_no;

  if (x > 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}
