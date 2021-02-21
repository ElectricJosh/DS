from _LCD_MCP23S17 import MCP23S17Backend
from machine import Timer

# clock is on bit 0
# RS is on bit 1

class LCDBackend:

    MCP23S17Ref = 0

    def __init__(self, LCD_SPI_Object, LCD_SPI_CS):
        self.MCP23S17Ref = MCP23S17Backend(LCD_SPI_Object, LCD_SPI_CS)
        Timer.sleep_us(50000)
        self.InitFunctionSet()
        Timer.sleep_us(4500)
        self.InitFunctionSet()
        Timer.sleep_us(200)
        self.InitFunctionSet()
        # now set the properties you want
        self.FunctionSet()
        self.DisplayOnOff()
        self.ClearScreen()
        self.EntryModeSet()

    # INITIALISING FUNCTIONS

    def InitFunctionSet(self): # D7 -> 00110000 <- D0 (0x30)
        self.RSValue(0)
        ToBank = self.MCP23S17Ref.WritePortA(0x30)
        self.ClockIn()

    def FunctionSet(self): # D7 -> 00111000 <- D0 (0x38)
        self.RSValue(0)
        ToBank = self.MCP23S17Ref.WritePortA(0x38)
        self.ClockIn()

    def DisplayOnOff(self): # D7 -> 00001100 <- D0 (0x0C) No cursor, no blink, display on
        self.RSValue(0)
        ToBank = self.MCP23S17Ref.WritePortA(0x0C)
        self.ClockIn()

    def ClearScreen(self): # D7 -> 00000001 <- D0 (0x01)
        self.RSValue(0)
        ToBank = self.MCP23S17Ref.WritePortA(0x01)
        self.ClockIn()
        Timer.sleep_us(2000)

    def EntryModeSet(self): # D7 -> 00000110 <- D0 (0x06)
        self.RSValue(0)
        ToBank = self.MCP23S17Ref.WritePortA(0x06)
        self.ClockIn()

    def ClockIn(self):
        Temp = self.MCP23S17Ref.ReadPortB() # Clock is on bit 0
        ClkOff = Temp & (0xFF - 0x01)
        ClkOn = ClkOff | 0x01

        self.MCP23S17Ref.WritePortB(ClkOff)
        Timer.sleep_us(1)
        self.MCP23S17Ref.WritePortB(ClkOn)
        Timer.sleep_us(1)
        self.MCP23S17Ref.WritePortB(ClkOff)
        Timer.sleep_us(100)

    def RSValue(self, value): # value should be 1 or 0
        Temp = self.MCP23S17Ref.ReadPortB() # RS is on bit 1
        Temp &= 0xFD # sets bit 1 to false
        value = value << 1
        value &= 0x02
        Temp |= value
        self.MCP23S17Ref.WritePortB(Temp)

    # DISPLAY CONTROL FUNCTIONS

    def WriteLine1(self, TextString): # parse 's' as an argument
        self.RSValue(0)
        self.MCP23S17Ref.WritePortA(0x80)
        self.ClockIn()

        b = bytearray()
        b.extend(TextString.encode())

        self.RSValue(1)
        for x in range(0, len(b)): # writes a char at a time
            self.MCP23S17Ref.WritePortA(b[x])
            self.ClockIn()

    def WriteLine2(self, TextString): # parse 's' as an argument
        self.RSValue(0)
        self.MCP23S17Ref.WritePortA(0xC0)
        self.ClockIn()

        b = bytearray()
        b.extend(TextString.encode())

        self.RSValue(1)
        for x in range(0, len(b)): # writes a char at a time
            self.MCP23S17Ref.WritePortA(b[x])
            self.ClockIn()