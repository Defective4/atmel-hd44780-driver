#include "../hd44780/directhd44780.cpp"

void runDirectExample() {
  DirectHD44780 lcd(PB0, PB1, PC0, PC1, PC2, PC3);
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
  lcd.writeLine("Hello", 5, 0);
  lcd.writeLine("World! \0", 8, 1);
}