#include "I2C.h"

#define MCP23008_IODIR 0x00
#define MCP23008_IPOL 0x01
#define MCP23008_GPINTEN 0x02
#define MCP23008_DEFVAL 0x03
#define MCP23008_INTCON 0x04
#define MCP23008_IOCON 0x05
#define MCP23008_GPPU 0x06
#define MCP23008_INTF 0x07
#define MCP23008_INTCAP 0x08
#define MCP23008_GPIO 0x09
#define MCP23008_OLAT 0x0A

// Declaration

class MCP23008_Driver
{
	public:
	MCP23008_Driver(void);
	static void Initialise(short ChipAddress);
	static void SpeedSetup(int CPUSpeed, int ClockSpeed);
	static void Write(short ChipAddress, short RegAddress, short DataToReg);
	static void Read(short ChipAddress, short RegAddress, short &DataToReg);
};

// Class Members

MCP23008_Driver::MCP23008_Driver()
{

}

void MCP23008_Driver::SpeedSetup(int CPUSpeed, int ClockSpeed)
{
	//I2C_Driver::IIC_Setup(0x03, 255); // fix this later
}

void MCP23008_Driver::Initialise(short ChipAddress)
{
	MCP23008_Driver::Write(ChipAddress, (short)MCP23008_IODIR, 0xFF); // input/output pin config
	MCP23008_Driver::Write(ChipAddress, (short)MCP23008_IPOL, 0xFF); // invert logic pin config
	MCP23008_Driver::Write(ChipAddress, (short)MCP23008_GPINTEN, 0x00); // interrupt on change config
	MCP23008_Driver::Write(ChipAddress, (short)MCP23008_DEFVAL, 0x00); // default value for interrupt comparison
	MCP23008_Driver::Write(ChipAddress, (short)MCP23008_INTCON, 0x00); // comparison bits
	MCP23008_Driver::Write(ChipAddress, (short)MCP23008_IOCON, 0x28); // IO config
	MCP23008_Driver::Write(ChipAddress, (short)MCP23008_GPPU, 0xFF); // pull up resistor
	MCP23008_Driver::Write(ChipAddress, (short)MCP23008_INTF, 0x00); // interrupt flag INTCAP
	//MCP23008_Driver::Write(ChipAddress, (short)MCP23008_INTCAP, 0x00); // interrupt freeze data GPIO
	//MCP23008_Driver::Write(ChipAddress, (short)MCP23008_GPIO, 0x00); // actual logic register // change back to 0x00
}

void MCP23008_Driver::Write(short ChipAddress, short RegAddress, short DataToReg)
{
	short Addressing = ((ChipAddress << 1) | 0x00) | 0x40; // 0x00 Master-Write Mode address bit

	I2C_Driver::SendMessage(Addressing, RegAddress, DataToReg);
}

void MCP23008_Driver::Read(short ChipAddress, short RegAddress, short &DataToReg)
{
	short Addressing = ((ChipAddress << 1) | 0x01) | 0x40; // 0x01 Master-Read Mode address bit

	I2C_Driver::ReceiveMessage(Addressing, RegAddress, DataToReg);
}