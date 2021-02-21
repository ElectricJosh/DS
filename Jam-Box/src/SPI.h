#include <avr/io.h>

#define SPI_SS 0x04
#define SPI_MOSI 0x08
#define SPI_MISO 0x10
#define SPI_SCK 0x20

class SPI_Driver // see page 215
{
	private:

	public:

	SPI_Driver(void);
	static void Master_Initialise(void);
	static void CS_Enable();
	static void CS_Disable();
	static short Master_TX(short Data);
};

SPI_Driver::SPI_Driver()
{

}

void SPI_Driver::CS_Enable()
{
	PORTB &= ~SPI_SS; // set low
}

void SPI_Driver::CS_Disable()
{
	PORTB |= SPI_SS; // set high
}

void SPI_Driver::Master_Initialise()
{
	DDRB |= SPI_MOSI; // set bit // output
	DDRB |= SPI_SCK; // set bit // output
	DDRB |= SPI_SS; // set bit // output
	DDRB &= ~SPI_MISO; // clear bit // input // Tilda inverts bits

	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0); // SPE = SPI enable (enables SPI bus), set to master mode, clock rate Fosc/16
}

short SPI_Driver::Master_TX(short Data) // used to read and write SPI
{
	SPDR = (Data & 0xFF); // Start transmission
	while(!(SPSR & (1<<SPIF))); // Wait for transmission complete
	return SPDR;
}

// All register see pg.19 and pg.428

// DDRD &= 0x01;
// PORTD |= 0x01; // LED on

// SPI

// SS = PortB2
// MOSI = PortB3
// MISO = PortB4
// SCK = PortB5

// Registers

// SPI Control Register pg.221
// SPI Status Resister pg.223
// SPI Data Register pg. 224

// SPIF reg in the status register (read only) is set by hardware when a serial transfer is complete
// I think it is cleared by reading the status register.

