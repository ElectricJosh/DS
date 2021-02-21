#include "MCP23S17.h"
#include <util/delay.h>
#include <string.h>

//#define F_CPU 8000000

class LCD_Driver
{
	private:

	public:
	static void Initialise();
	static void InitFunctionSet();
	static void FunctionSet();
	static void DisplayOnOff();
	static void ClearScreen();
	static void EntryModeSet();
	static void ClockIn();
	static void RSValue(short value);
	static void WriteLine1(char TextString[]);
	static void WriteLine2(char TextString[]);
};

void LCD_Driver::Initialise()
{
	MCP23S17_Driver::Initialise();

	_delay_us(50000);
	LCD_Driver::InitFunctionSet();
	_delay_us(4500);
	LCD_Driver::InitFunctionSet();
	_delay_us(200);
	LCD_Driver::InitFunctionSet();
	// now set the properties you want
	LCD_Driver::FunctionSet();
	LCD_Driver::DisplayOnOff();
	LCD_Driver::ClearScreen();
	LCD_Driver::EntryModeSet();
}

 void LCD_Driver::InitFunctionSet() // D7 -> 00110000 <- D0 (0x30)
 {
	LCD_Driver::RSValue(0);
	MCP23S17_Driver::WritePortA(0x30);
	LCD_Driver::ClockIn();
 }

 void LCD_Driver::FunctionSet() // D7 -> 00111000 <- D0 (0x38)
 {
	LCD_Driver::RSValue(0);
	MCP23S17_Driver::WritePortA(0x38);
	LCD_Driver::ClockIn();
 }

 void LCD_Driver::DisplayOnOff() // # D7 -> 00001100 <- D0 (0x0C) No cursor, no blink, display on
 {
	LCD_Driver::RSValue(0);
	MCP23S17_Driver::WritePortA(0x0C);
	LCD_Driver::ClockIn();
 }

 void LCD_Driver::ClearScreen() // # D7 -> 00000001 <- D0 (0x01)
 {
	LCD_Driver::RSValue(0);
	MCP23S17_Driver::WritePortA(0x01);
	LCD_Driver::ClockIn();
	_delay_us(2000);
 }

 void LCD_Driver::EntryModeSet() // # D7 -> 00000110 <- D0 (0x06)
 {
	LCD_Driver::RSValue(0);
	MCP23S17_Driver::WritePortA(0x06);
	LCD_Driver::ClockIn();
 }

 void LCD_Driver::ClockIn()
 {
	short Temp = MCP23S17_Driver::ReadPortB(); // # Clock is on bit 0
	short ClkOff = Temp & (0xFF - 0x01);
	short ClkOn = ClkOff | 0x01;

	MCP23S17_Driver::WritePortB(ClkOff);
	_delay_us(1);
	MCP23S17_Driver::WritePortB(ClkOn);
	_delay_us(1);
	MCP23S17_Driver::WritePortB(ClkOff);
	_delay_us(100);
 }

 void LCD_Driver::RSValue(short value)
 { 
	// # value should be 1 or 0
	short Temp = MCP23S17_Driver::ReadPortB(); // # RS is on bit 1
	Temp &= 0xFD; // # sets bit 1 to false
	value = value << 1;
	value &= 0x02;
	Temp |= value;
	MCP23S17_Driver::WritePortB(Temp);
 }
 
 void LCD_Driver::WriteLine1(char TextString[]) // parse 's' as an argument
 { 
	LCD_Driver::RSValue(0);
	MCP23S17_Driver::WritePortA(0x80);
	LCD_Driver::ClockIn();

	LCD_Driver::RSValue(1);	
	
	for(unsigned int i = 0; i < strlen(TextString); i++)
	{
		MCP23S17_Driver::WritePortA(TextString[i]); //: # writes a char at a time
		LCD_Driver::ClockIn();
	}	
 }

 void LCD_Driver::WriteLine2(char TextString[]) // parse 's' as an argument
 { 
	LCD_Driver::RSValue(0);
	MCP23S17_Driver::WritePortA(0xC0);
	LCD_Driver::ClockIn();

	LCD_Driver::RSValue(1);
	
	for(unsigned int i = 0; i < strlen(TextString); i++)
	{
		MCP23S17_Driver::WritePortA(TextString[i]); //: # writes a char at a time
		LCD_Driver::ClockIn();
	}
 }
 