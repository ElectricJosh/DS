#include "Meta.h"
#include "MAX517DAC.h"

class Synth
{
	public:
	static void SetupTimer();
	static float FindSamplePeriod();
	static void ScaleFinder();
	static void OutputSignal(); // short osc, short level, short overtone, short AM, short FM
};

void Synth::SetupTimer() // for timer 1
{
	TCCR1A = 0; // this register can be used for frequency generation if needs be
	TCCR1B = 0x01; // set pre-scaler to no scaling 1:1
	TCCR1C = 0;
	TCNT1 = 0x0000; // clears counter 1 (16 bit)
	TIMSK1 = 0x00; // Interrupt mask reg // contains flag for interrupts, match interrupts A and B as well as overflow interrupt
}

int Watch_Ticks = 0; // delete later

float Synth::FindSamplePeriod() // see pg50 of datasheet for clock speed
{
	int Ticks = TCNT1L | (TCNT1H << 8);
	Watch_Ticks = Ticks;
	float TimeElapsed = ((float)Ticks)/8000000.0f; // clock cycles x 1Mhz period // if CLKPR prescaler is set to 0 then 8Mhz
	TCNT1 = 0x0000; // clears counter // does not optimize away
	return TimeElapsed;
}

short Maj_SemiTone_Offset[] = {0,2,4,5,7,9,11, 12,14,16,17,19,21,23, 24,26,28,29,31,33,35};
float CurrentScale[8]; // contains an array of frequency values


void Synth::ScaleFinder() // return array of 8 frequency constants
{
	for(short i = 0; i < 8; i++)
	{
		CurrentScale[i] = NoteFrequency[Meta_Root + Maj_SemiTone_Offset[i + Meta_KeyMode + Meta_RelMode] - Maj_SemiTone_Offset[Meta_KeyMode]];
		// Starting offset + moving offset - static mode compensation offset // don't change
	}	
}

float incrementer = 0;
bool SquareLevel = false;

void Synth::OutputSignal()
{
	// Find frequency
	
	short ButtonNumber = ButtonController::ReadBitNumber(); // reads one button, lowest has priority

	if(ButtonNumber == 8) // if nothing is pressed
	{
		return;
	}
	float ToPlay = CurrentScale[ButtonNumber]; // ToPlay = frequency value
	// Synth
	float SamplePeriod = Synth::FindSamplePeriod();
	incrementer += SamplePeriod;

	float HalfPeriod = 0.5f/(ToPlay); // 50% duty cycle, will modulate this later
	
	while(incrementer > HalfPeriod)
	{
		incrementer -= HalfPeriod;
		SquareLevel = !SquareLevel;
	}
	
	uint8_t Amplitude = 0;
	
	if(SquareLevel)
	{
		Amplitude = Meta_Level; // * AM
	}
	else
	{
		Amplitude = 0;
	}

	MAX517_Driver::WriteByte(Amplitude);
}