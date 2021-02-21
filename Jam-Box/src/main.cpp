#define F_CPU 8000000

//#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "Synth.h"

bool Global_Mode = true; // default to play mode

int main(void)
{
	// Enable 8Mhz internal clock // see page 60
	CLKPR = 0x80; // enable clock pre-scaler change, bit reset when prescaler is set
	CLKPR = 0x00; // set clock prescaler bits to 0

	DDRD &= ~(1 << DDD2);		// set as input, mode button
	PORTD |= (1 << PORTD2);		// pull up input

	DDRD &= ~(1 << DDD1);		// set as input, left button
	PORTD |= (1 << PORTD1);		// pull up input

	DDRD &= ~(1 << DDD0);		// set as input, right button
	PORTD |= (1 << PORTD0);		// pull up input

	DDRB &= ~(1 << DDB1);		// setup external switch input pin
	PORTB |= (1 << PORTB1);		// setup input with pull-up

	EICRA = 0xFF;				// all rising edge
	EIMSK = 0x01;				// enables interrupts, sets the INT0 register
	EIFR = 0xFF;				// clear interrupt flags
	PCICR |= (1 << PCIE0);		// set PCIE0 to enable PCMSK0 scan
	PCIFR |= (1 << PCIF2);		// listen on pins 16 to 23
	PCMSK2 |= (1 << PCINT18);	// set PCINT0 to trigger an interrupt on state change
	sei();						// turn on interrupts
	
	Synth::SetupTimer();	
	Meta::Initialise(); // sets up button controller and LCD
	Synth::ScaleFinder();
	
	LCD_Driver::WriteLine1("Play");
	while (1)
	{
		if (Global_Mode == 0x01) // Play mode
		{
			Synth::OutputSignal();
		}
		else // Meta mode
		{
			Meta::SettingHandler();			
		}
	}
}

ISR(INT0_vect) // Mode toggle
{
	Global_Mode = !Global_Mode;
	LCD_Driver::ClearScreen();
	if(Global_Mode)
	{
		LCD_Driver::WriteLine1("Play");
		Synth::ScaleFinder();
	}
	_delay_ms(400);
}