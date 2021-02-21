#include "SPI.h"

#define MCP23S17_ChipAddress 0x40

#define MCP23S17_IODIRA 0x00
#define MCP23S17_IODIRB 0x01
#define MCP23S17_IPOLA 0x02
#define MCP23S17_IPOLB 0x03
#define MCP23S17_GPINTENA 0x04
#define MCP23S17_GPINTENB 0x05
#define MCP23S17_DEFVALA 0x06
#define MCP23S17_DEFVALB 0x07
#define MCP23S17_INTCONA 0x08
#define MCP23S17_INTCONB 0x09
#define MCP23S17_IOCONA 0x0A
#define MCP23S17_IOCONB 0x0B
#define MCP23S17_GPPUA 0x0C
#define MCP23S17_GPPUB 0x0D
#define MCP23S17_GPIOA 0x12
#define MCP23S17_GPIOB 0x13

class MCP23S17_Driver
{
	private:

	public:

	static void Initialise(void);
	static void Write(short Reg, short Data);
	static short Read(short Reg);
	static void WritePortA(short value);
	static void WritePortB(short value);
	static short ReadPortA();
	static short ReadPortB();
	static short BitOrderPatch(short value);
};

void MCP23S17_Driver::Initialise() // Setup SPI and set all default register values
{
	SPI_Driver::Master_Initialise();

	SPI_Driver::CS_Disable(); // Chip disabled, active low by default

	MCP23S17_Driver::Write(MCP23S17_IOCONA, 0x28);
	MCP23S17_Driver::Write(MCP23S17_IOCONB, 0x28);

	MCP23S17_Driver::Write(MCP23S17_IODIRA, 0x00);
	MCP23S17_Driver::Write(MCP23S17_IODIRB, 0x00);

	MCP23S17_Driver::Write(MCP23S17_IPOLA, 0x00);
	MCP23S17_Driver::Write(MCP23S17_IPOLB, 0x00);

	MCP23S17_Driver::Write(MCP23S17_GPINTENA, 0x00);
	MCP23S17_Driver::Write(MCP23S17_GPINTENB, 0x00);

	MCP23S17_Driver::Write(MCP23S17_DEFVALA, 0x00);
	MCP23S17_Driver::Write(MCP23S17_DEFVALB, 0x00);

	MCP23S17_Driver::Write(MCP23S17_INTCONA, 0x00);
	MCP23S17_Driver::Write(MCP23S17_INTCONB, 0x00);

	MCP23S17_Driver::Write(MCP23S17_GPPUA, 0x00);
	MCP23S17_Driver::Write(MCP23S17_GPPUB, 0x00);

	// # Initialise Outputs

	MCP23S17_Driver::Write(MCP23S17_GPIOA, 0x00);
	MCP23S17_Driver::Write(MCP23S17_GPIOB, 0x00);
}

void MCP23S17_Driver::Write(short Reg, short Data)
{
	SPI_Driver::CS_Disable();
	SPI_Driver::CS_Enable();
	SPI_Driver::Master_TX(MCP23S17_ChipAddress);
	SPI_Driver::Master_TX(Reg);
	SPI_Driver::Master_TX(Data);
	SPI_Driver::CS_Disable();
}

short MCP23S17_Driver::Read(short Reg)
{
	SPI_Driver::CS_Disable();
	SPI_Driver::CS_Enable();
	SPI_Driver::Master_TX((MCP23S17_ChipAddress + 0x01)); // the read address has a read bit that needs to be enabled
	SPI_Driver::Master_TX(Reg);
	short Data = SPI_Driver::Master_TX(0xFF);
	SPI_Driver::CS_Disable();
	return Data;
}

void MCP23S17_Driver::WritePortA(short value)
{
	value = BitOrderPatch(value); // only needed on the LCD controlling port
	MCP23S17_Driver::Write(MCP23S17_GPIOA, value);
}

void MCP23S17_Driver::WritePortB(short value)
{
	MCP23S17_Driver::Write(MCP23S17_GPIOB, value);
}

short MCP23S17_Driver::ReadPortA()
{
	return MCP23S17_Driver::BitOrderPatch(MCP23S17_Driver::Read(MCP23S17_GPIOA));
}

short MCP23S17_Driver::ReadPortB()
{
	return MCP23S17_Driver::Read(MCP23S17_GPIOB);
}

short MCP23S17_Driver::BitOrderPatch(short value)
{
	short temp = 0;
	temp |= ((0x01 & value)<<7);
	temp |= ((0x02 & value)<<5);
	temp |= ((0x04 & value)<<3);
	temp |= ((0x08 & value)<<1);
	temp |= ((0x10 & value)>>1);
	temp |= ((0x20 & value)>>3);
	temp |= ((0x40 & value)>>5);
	temp |= ((0x80 & value)>>7);
	temp &= 0xFF;
	return temp;
}