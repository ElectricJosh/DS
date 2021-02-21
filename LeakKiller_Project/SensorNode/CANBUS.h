#ifndef CANBUS_h
#define CANBUS_h

#include "MCP2515.h"

typedef struct
{
  unsigned long ID; // 32 bits to hold 29 bit ID
  byte Length;
  byte Data[8];
} CAN_M;

class CAN
{
  private:

  public:
    CAN(void);
    static void Initialise(byte ScalingFactor);
    static bool Get_Message(CAN_M *M);
    static void Send_Message(CAN_M *M, bool ExtendedFlag); // I don't need a pointer here
};

#endif
