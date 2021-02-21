#include <EEPROM.h>
#include "CANBUS.h"

#define LEDPin A2
#define Sensor1Pin A5
#define Sensor2Pin A4

int NodeID = 0;
int MasterID = 10;
int AllocationID = 9;
unsigned long cooldown = 0; // stops errors spamming the CANBUS

bool StatusFlag = false;
CAN_M MessageRX;
CAN_M MessageTX;

void setup()
{
  Serial.begin(9600);
  CAN::Initialise(0); // intialised at 500 kb/s
  attachInterrupt(digitalPinToInterrupt(3), ButtonPressHandler, FALLING); // 100k external pull-up resistor
  pinMode(Sensor1Pin, INPUT);
  pinMode(Sensor2Pin, INPUT);
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, StatusFlag);

  // attempt to find a previously allocated ID in eeprom
  EEPROM.get(0, NodeID);
}

void loop()
{
  ///////////////////////////////////////////////////////
  // UART Pins: Manual ID Checker
  ///////////////////////////////////////////////////////

  if (Serial.available() > 0) // attach UART wires and request Node ID
  {
    String temp = Serial.readString();
    if (temp == "id") // works
    {
      Serial.println(String(NodeID));
    }
  }

  ///////////////////////////////////////////////////////
  // Error Flag Sender
  ///////////////////////////////////////////////////////

  bool ErrorFlag = false;
  byte ErrorStatusByte = 0;
  if (analogRead(Sensor1Pin) > 127)
  {
    ErrorFlag = true;
    ErrorStatusByte |= 0x01; // status bit 0
  }
  if (analogRead(Sensor2Pin) > 127)
  {
    ErrorFlag = true;
    ErrorStatusByte |= 0x02; // status bit 1
  }

  if (ErrorFlag == true)
  {
    if (NodeID != -1)
    {
      if (millis() > cooldown)
      {
        // send error message
        BlankTXMessage(NodeID);
        MessageTX.Data[0] = ErrorStatusByte;
        CAN::Send_Message(&MessageTX, false);
        cooldown = (millis()) + 15000; // 15 second cooldown
      }
    }
  }

  ///////////////////////////////////////////////////////
  // Allocation ID Channel Listener
  ///////////////////////////////////////////////////////

  if (NodeID != -1)
  {
    if (CAN::Get_Message(&MessageRX) == true)
    {
      if (MessageRX.ID == AllocationID)
      {
        int QuestionedID = (((int)MessageRX.Data[0]) | (((int)(MessageRX.Data[1] & 0x07)) << 8)); // first 11 bits of data (standard frame ID)
        if (QuestionedID == NodeID) // if this node's ID on the network is being questioned then the node must acknowledge to stop duplicate node IDs being assigned.
        {
          BlankTXMessage(NodeID);
          MessageTX.Data[7] = 0xFF; // tells the master to ignore this message
          CAN::Send_Message(&MessageTX, false);
        }
      }
    }
  }

  ///////////////////////////////////////////////////////
  // Allocation ID Polling
  ///////////////////////////////////////////////////////

  if (StatusFlag == true)
  {
    for (int x = 11; x < 2000; x++) // 2000 max number of nodes
    {
restart:
      BlankTXMessage(AllocationID);
      MessageTX.Data[0] = (byte)(x & 0xFF);
      MessageTX.Data[1] = (byte)((x >> 8) & 0x07); // for an 11 bit identifier.
      MessageTX.Data[7] = 0xFF; // tells the master to ignore this message
      CAN::Send_Message(&MessageTX, false);
      delay(3000); // wait for response.

      while (CAN::Get_Message(&MessageRX) == true)
      {
        if (MessageRX.ID == x)
        {
          x++;
          goto restart;
        }        
      }

      NodeID = x;
      EEPROM.put(0, NodeID);
      StatusFlag = false;
      digitalWrite(LEDPin, StatusFlag);
      Serial.println("ID Allocated: " + String(x));
      break;
    }
  }
}

void ButtonPressHandler()
{
  StatusFlag = true;
  digitalWrite(LEDPin, StatusFlag);
  NodeID = -1;
  EEPROM.put(0, NodeID); // reset current ID
  Serial.println("ID Reset");
}

void BlankTXMessage(int identifier)
{
  MessageTX.ID = identifier;
  MessageTX.Length = 8;
  for (int i = 0; i < 8; i++)
  {
    MessageTX.Data[i] = 0; // needs no data to send.
  }
}
