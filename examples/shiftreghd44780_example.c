#include "../hd44780/shiftreghd44780.cpp"

void runShiftRegExample() {
  ShiftRegHD44780 lcd(PC0, PC1, PC2);
  lcd.init();
  uint8_t heart[] = {
    0b00000,
    0b01010,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000,
    0b00000
  };
  lcd.createChar(0, heart);
  lcd.writeLine("Hello world", 11, 0);
  lcd.writeLine("via 74hc595 \0", 13, 1);
}