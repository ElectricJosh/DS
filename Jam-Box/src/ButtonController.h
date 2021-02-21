#include "MCP23008.h"

#define ExpanderAddress 0x01 // A0 = 1, A1 = 0, A2 = 0

class ButtonController
{
	public:
	static void Setup();
	static short ReadMask();
	static short ReadBitNumber();
};

void ButtonController::Setup() // Initialize the expander chips
{
	MCP23008_Driver::Initialise(ExpanderAddress);
}

short ButtonController::ReadMask() // Read as a byte of notes
{
	short notes = 0x00; // if it returns 3 then there was a i2c com issue
	MCP23008_Driver::Read(ExpanderAddress, MCP23008_GPIO, notes); // ChipAddress, RegAddress, &DataToReg
	notes = MCP23S17_Driver::BitOrderPatch(notes); // notes are wired the wrong way // ugly hack
	return notes; // return note byte
}

short ButtonController::ReadBitNumber() // Read as a setting LSB has priority
{
	short notes = 0x00;
	MCP23008_Driver::Read(ExpanderAddress, MCP23008_GPIO, notes); // ChipAddress, RegAddress, &DataToReg
	notes = MCP23S17_Driver::BitOrderPatch(notes); // notes are wired the wrong way // ugly hack
	
	int count = 0;
	while(count < 8) // while loop is faster
	{
		if( (notes & (1 << count)) > 0)
		{
			return count;			
		}
		count++;
	}
	return count++; // return 8 if nothing selected
}

