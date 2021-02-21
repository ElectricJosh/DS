#include <avr/eeprom.h>
#include "LCD.h"
#include "ButtonController.h"
#include "NoteBank.h"

#define EEPROM_Root 0x00
#define EEPROM_Mode 0x01
#define EEPROM_RelMode 0x02
#define EEPROM_Osc 0x03
#define EEPROM_Overtone 0x04
#define EEPROM_AM 0x05
#define EEPROM_FM 0x06
#define EEPROM_Level 0x07

// Settings storage in RAM // Zero values seem to cause errors in EEPROM
short Meta_Root; // root note e.g. c3
short Meta_KeyMode; // Major by default
short Meta_RelMode; // Add this later [unimplemented]
short Meta_Osc; // sine by default [unimplemented]
short Meta_Overtone; // no overtone [unimplemented]
short Meta_AM; // no modulation [unimplemented]
short Meta_FM; // no modulation [unimplemented]
short Meta_Level; // max volume by default

class Meta
{
	private:
	static void HandleChange(short &Meta_Value, short Upper);
	public:
	static void Initialise();
	static void SettingHandler();
};

void Meta::Initialise()
{
	Meta_Root = 0x19;
	Meta_KeyMode = 0x00;
	Meta_RelMode = 0x00;
	Meta_Osc = 0x00;
	Meta_Overtone = 0x00;
	Meta_AM = 0x00;
	Meta_FM = 0x00;
	Meta_Level = 0xFE;

	ButtonController::Setup();
	LCD_Driver::Initialise();
	
	// Load settings from EEPROM
	
	if(eeprom_read_byte((uint8_t*)EEPROM_Root) == 0xFF) // if null (0xff) // eeprom_read_byte((uint8_t*)46);
	{
		eeprom_write_byte((uint8_t*)EEPROM_Root, Meta_Root);
	}
	else
	{
		Meta_Root = eeprom_read_byte((uint8_t*)EEPROM_Root);
	}
	
	if(eeprom_read_byte((uint8_t*)EEPROM_Mode) == 0xFF) // if null (0xff) // uint8_t eeprom_read_byte (const uint8_t *__p) __ATTR_PURE__;
	{
		eeprom_write_byte((uint8_t*)EEPROM_Mode, Meta_KeyMode);
	}
	else
	{
		Meta_KeyMode = eeprom_read_byte((uint8_t*)EEPROM_Mode);
	}
	
	if(eeprom_read_byte((uint8_t*)EEPROM_RelMode) == 0xFF)
	{
		eeprom_write_byte((uint8_t*)EEPROM_RelMode, Meta_RelMode);
	}
	else
	{
		Meta_RelMode = eeprom_read_byte((uint8_t*)EEPROM_RelMode);
	}

	if(eeprom_read_byte((uint8_t*)EEPROM_Osc) == 0xFF)
	{
		eeprom_write_byte((uint8_t*)EEPROM_Osc, Meta_Osc);
	}
	else
	{
		Meta_Osc = eeprom_read_byte((uint8_t*)EEPROM_Osc);
	}

	if(eeprom_read_byte((uint8_t*)EEPROM_Overtone) == 0xFF)
	{
		eeprom_write_byte((uint8_t*)EEPROM_Overtone, Meta_Overtone);
	}
	else
	{
		Meta_Overtone = eeprom_read_byte((uint8_t*)EEPROM_Overtone);
	}

	if(eeprom_read_byte((uint8_t*)EEPROM_AM) == 0xFF)
	{
		eeprom_write_byte((uint8_t*)EEPROM_AM, Meta_AM);
	}
	else
	{
		Meta_AM = eeprom_read_byte((uint8_t*)EEPROM_AM);
	}

	if(eeprom_read_byte((uint8_t*)EEPROM_FM) == 0xFF)
	{
		eeprom_write_byte((uint8_t*)EEPROM_FM, Meta_FM);
	}
	else
	{
		Meta_FM = eeprom_read_byte((uint8_t*)EEPROM_FM);
	}

	if(eeprom_read_byte((uint8_t*)EEPROM_Level) == 0xFF)
	{
		eeprom_write_byte((uint8_t*)EEPROM_Level, Meta_Level);
	}
	else
	{
		Meta_Level = eeprom_read_byte((uint8_t*)EEPROM_Level);
	}
}

void Meta::SettingHandler() // setting held down
{
	switch (ButtonController::ReadBitNumber()) // update LCD and EEPROM based on the setting number
	{
		case 0: // Root
		{
			Meta::HandleChange(Meta_Root, 50);
			if(eeprom_read_byte((uint8_t*)EEPROM_Root) != Meta_Root) // if null (0xff) // eeprom_read_byte((uint8_t*)46);
			{
				eeprom_write_byte((uint8_t*)EEPROM_Root, Meta_Root);
			}
			
			LCD_Driver::ClearScreen();
			LCD_Driver::WriteLine1("Root Note");
			char temp1[4] = {NotesString[Meta_Root][0], NotesString[Meta_Root][1], NotesString[Meta_Root][2], NotesString[Meta_Root][3]};
			LCD_Driver::WriteLine2(temp1);
			break;
		}
		case 1: // Mode
		{
			Meta::HandleChange(Meta_KeyMode, 6);
			if(eeprom_read_byte((uint8_t*)EEPROM_Root) != Meta_KeyMode) // if null (0xff) // eeprom_read_byte((uint8_t*)46);
			{
				eeprom_write_byte((uint8_t*)EEPROM_Root, Meta_KeyMode);
				Meta_RelMode = 0; // reset and save the relative mode
				eeprom_write_byte((uint8_t*)EEPROM_Root, Meta_RelMode);
			}

			LCD_Driver::ClearScreen();
			LCD_Driver::WriteLine1("Key Mode");
			char temp2[11] = {ModeNames[Meta_KeyMode][0], ModeNames[Meta_KeyMode][1], ModeNames[Meta_KeyMode][2], ModeNames[Meta_KeyMode][3], ModeNames[Meta_KeyMode][4], ModeNames[Meta_KeyMode][5], ModeNames[Meta_KeyMode][6], ModeNames[Meta_KeyMode][7], ModeNames[Meta_KeyMode][8], ModeNames[Meta_KeyMode][9], ModeNames[Meta_KeyMode][10]};
			LCD_Driver::WriteLine2(temp2);
			break;
		}
		case 2: // Relative Mode [unimplemented]
		{
			Meta::HandleChange(Meta_RelMode, 6);
			if(eeprom_read_byte((uint8_t*)EEPROM_Root) != Meta_RelMode) // if null (0xff) // eeprom_read_byte((uint8_t*)46);
			{
				eeprom_write_byte((uint8_t*)EEPROM_Root, Meta_RelMode);
			}

			LCD_Driver::ClearScreen();
			LCD_Driver::WriteLine1("Relative Mode");			
			short modeshift = Meta_KeyMode + Meta_RelMode;
			while(modeshift > 6)
			{
				modeshift -= 7;
			}			
			char temp3[11] = {ModeNames[modeshift][0], ModeNames[modeshift][1], ModeNames[modeshift][2], ModeNames[modeshift][3], ModeNames[modeshift][4], ModeNames[modeshift][5], ModeNames[modeshift][6], ModeNames[modeshift][7], ModeNames[modeshift][8], ModeNames[modeshift][9], ModeNames[modeshift][10]};
			LCD_Driver::WriteLine2(temp3);
			break;
		}
		case 3: // Oscillator [unimplemented]
		{
			//Meta::HandleChange(Meta_Osc, 3);
			if(eeprom_read_byte((uint8_t*)EEPROM_Root) != Meta_Osc) // if null (0xff) // eeprom_read_byte((uint8_t*)46);
			{
				eeprom_write_byte((uint8_t*)EEPROM_Root, Meta_Osc);
			}

			LCD_Driver::ClearScreen();
			LCD_Driver::WriteLine1("Oscillator");
			//LCD_Driver::WriteLine2(Meta_Osc);
			break;
		}
		case 4: // Overtone [unimplemented]
		{
			//Meta::HandleChange(Meta_Overtone, 3);
			if(eeprom_read_byte((uint8_t*)EEPROM_Root) != Meta_Overtone) // if null (0xff) // eeprom_read_byte((uint8_t*)46);
			{
				eeprom_write_byte((uint8_t*)EEPROM_Root, Meta_Overtone);
			}

			LCD_Driver::ClearScreen();
			LCD_Driver::WriteLine1("Overtone");
			//LCD_Driver::WriteLine2(Meta_Overtone);
			break;
		}
		case 5: // AM [unimplemented]
		{
			//Meta::HandleChange(Meta_AM, 100);
			if(eeprom_read_byte((uint8_t*)EEPROM_Root) != Meta_AM) // if null (0xff) // eeprom_read_byte((uint8_t*)46);
			{
				eeprom_write_byte((uint8_t*)EEPROM_Root, Meta_AM);
			}

			LCD_Driver::ClearScreen();
			LCD_Driver::WriteLine1("AM Index");
			//LCD_Driver::WriteLine2(Meta_AM);
			break;
		}
		case 6: // FM [unimplemented]
		{
			//Meta::HandleChange(Meta_FM, 100);
			if(eeprom_read_byte((uint8_t*)EEPROM_Root) != Meta_FM) // if null (0xff) // eeprom_read_byte((uint8_t*)46);
			{
				eeprom_write_byte((uint8_t*)EEPROM_Root, Meta_FM);
			}

			LCD_Driver::ClearScreen();
			LCD_Driver::WriteLine1("FM Index");
			//LCD_Driver::WriteLine2(Meta_FM);
			break;
		}
		case 7: // Level
		{
			Meta::HandleChange(Meta_Level, 254);
			if(eeprom_read_byte((uint8_t*)EEPROM_Root) != Meta_Level) // if null (0xff) // eeprom_read_byte((uint8_t*)46);
			{
				eeprom_write_byte((uint8_t*)EEPROM_Root, Meta_Level);
			}

			LCD_Driver::ClearScreen();
			LCD_Driver::WriteLine1("Volume");
			char temp8[10] = {};
			sprintf(temp8,"%d",Meta_Level);
			LCD_Driver::WriteLine2(temp8);
			break;
		}
		case 8: // Nothing selected
		{
			LCD_Driver::ClearScreen();
			LCD_Driver::WriteLine1("Settings"); // Might show key info instead Key, Mode, Relative Mode
			break;
		}
	}
	_delay_ms(200);
}

void Meta::HandleChange(short &Meta_Value, short Upper)
{
	bool UpButton = false; // replace with hardware pin check
	bool DownButton = false; // replace with hardware pin check

	// Check hardware switches
	if((PIND & 0x01) == 0) // right button // active low
	{
		UpButton = true;
	}
	if((PIND & 0x02) == 0) // left button // active low
	{
		DownButton = true;
	}

	// Increment/Decrement
	if(UpButton && DownButton)
	{
		// special function?
	}
	else if(UpButton)
	{
		Meta_Value++;
	}
	else if(DownButton)
	{
		Meta_Value--;
	}

	// Check overload
	if(Meta_Value < 0)
	{
		Meta_Value = 0;
	}
	if(Meta_Value > Upper)
	{
		Meta_Value = Upper;
	}
}

