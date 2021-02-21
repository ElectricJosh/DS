//#include "I2C.h"

/*

From Data Sheet

The MAX517/MAX518/MAX519 are receive-only devices
and must be controlled by a bus master device. They
operate at SCL rates up to 400kHz. A master device
sends information to the devices by transmitting their
address over the bus and then transmitting the desired
information. Each transmission consists of a START
condition, the MAX517/MAX518/MAX519’s programmable
slave-address, one or more command-byte/output-
byte pairs (or a command byte alone, if it is the last
byte in the transmission), and finally, a STOP condition
(Figure 4).

*/

#define MAX517Address 0x5E // see data sheet for the weird addressing

class MAX517_Driver
{
	public:
	static void WriteByte(short Output);
};

void MAX517_Driver::WriteByte(short Output)
{
	I2C_Driver::SendMessage(MAX517Address,0x00,Output); // have a look at the data sheet I think there is a command byte 0x00
}