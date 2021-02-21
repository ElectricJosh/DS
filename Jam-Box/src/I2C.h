#include <avr/io.h>

// DECLARATION

class I2C_Driver
{
	private:

	public:

	//I2C_Driver(void);
	static void IIC_SpeedSetup(short PreScale, short BitRate);
	static void SetAddressPointer(short Address, short Reg);
	static void SendMessage(short Address, short Reg, short Data);
	static void ReceiveMessage(short Address, short Reg, short &Data); // Receive
};

// METHODS
/*
I2C_Driver::I2C_Driver()
{
	// No instances all static members
}
*/
void I2C_Driver::IIC_SpeedSetup(short PreScale, short BitRate) // SCL_Freq = CPU_Freq/(16 + 2(TWBR)(Pre-scaler value))
{
	TWSR = TWSR |= PreScale; // = 0x02 // see pg.293 for how the pre-scaler bits are encoded 1,4,16,64
	TWBR = BitRate;	// = 100
}

void I2C_Driver::SetAddressPointer(short Address, short Reg) // because you need to set addresses to read from using write mode
{
	// START
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // start condition

	while (!(TWCR & (1<<TWINT))); // wait for hardware to say operation is complete

	if ((TWSR & 0xF8) != 0x08) // mask data and check for start condition
	{
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); // transmit stop condition.
		return;
	}

	// Send and acknowledge slave address

	TWDR = (Address & 0xFE); // load slave address with write bit
	TWCR = (1<<TWINT) | (1<<TWEN); // start transmission of address

	while (!(TWCR & (1<<TWINT))); // wait for hardware to say operation is complete

	if ((TWSR & 0xF8) != 0x18) // check SR for address ACK
	{
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); // transmit stop condition.
		return;
	}
	
	// Send and acknowledge slave register to write to

	TWDR = (Reg & 0xFF);
	TWCR = (1<<TWINT) | (1<<TWEN); // start transmission

	while (!(TWCR & (1<<TWINT))); // wait for hardware to say operation is complete

	if ((TWSR & 0xF8) != 0x28) // check SR for data ACK
	{
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); // transmit stop condition.
		return;
	}

	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); // transmit stop condition.
}

void I2C_Driver::SendMessage(short Address, short Reg, short Data)
{
	// START
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // start condition

	while (!(TWCR & (1<<TWINT))); // wait for hardware to say operation is complete

	if ((TWSR & 0xF8) != 0x08) // mask data and check for start condition
	{
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); // transmit stop condition.
		return;
	}

	// Send and acknowledge slave address

	TWDR = (Address & 0xFF);
	TWCR = (1<<TWINT) | (1<<TWEN); // start transmission

	while (!(TWCR & (1<<TWINT))); // wait for hardware to say operation is complete

	if ((TWSR & 0xF8) != 0x18) // check SR for address ACK
	{
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); // transmit stop condition.
		return;
	}

	// Send and acknowledge slave register to write to

	TWDR = (Reg & 0xFF);
	TWCR = (1<<TWINT) | (1<<TWEN); // start transmission

	while (!(TWCR & (1<<TWINT))); // wait for hardware to say operation is complete

	if ((TWSR & 0xF8) != 0x28) // check SR for data ACK
	{
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); // transmit stop condition.
		return;
	}

	// Send and acknowledge data to write

	TWDR = Data; // load data
	TWCR = (1<<TWINT) | (1<<TWEN); // start transmission

	while (!(TWCR & (1<<TWINT))); // wait for hardware to say operation is complete

	if ((TWSR & 0xF8) != 0x28) // check SR for data ACK
	{
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); // transmit stop condition.
		return;
	}

	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); // transmit stop condition.
}

void I2C_Driver::ReceiveMessage(short Address, short Reg, short &Data) // see pg.7 of the mcp23008 datasheet, pay attention to the sequential read opperation at the bottom of the diagram
{

	I2C_Driver::SetAddressPointer(Address, Reg);

	// START

	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // TWINT = pulls SCL low, TWSTA = start condition, sets I/O pins for IIC use

	while (!(TWCR & (1<<TWINT))); // wait for hardware to say operation is complete

	if ((TWSR & 0xF8) != 0x08)  // mask data and check for start condition
	{
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); // transmit stop condition.
		return;
	}
	// Send and acknowledge slave address

	TWDR = (Address & 0xFF);

	TWCR = (1<<TWINT) | (1<<TWEN); // start transmission of address

	while (!(TWCR & (1<<TWINT))); // wait for hardware to say operation is complete

	if ((TWSR & 0xF8) != 0x40) // check SR for address ACK
	{
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); // transmit stop condition.
		return;
	}
	// Data Request

	TWDR = 0xFE;

	TWCR = (1<<TWINT) | (1<<TWEN); // start transmission

	while (!(TWCR & (1<<TWINT))); // wait for hardware to say operation is complete

	if ((TWSR & 0xF8) != 0x58) // check SR for data ACK // 0x58  This error is still an issue!!! but seems to work
	{
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); // transmit stop condition.
		return;
	}

	Data = TWDR; // read last byte of data written to the register

	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); // transmit stop condition.
	// do i need to wait for a confirmation
}

// Code sample at pg.270
