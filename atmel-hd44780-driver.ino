#include "hd44780.cpp"
#ifndef F_CPU
#define F_CPU 1000000
#endif

int main(void) {
  HD44780 lcd(PB0, PB1, PC0, PC1, PC2, PC3);
  lcd.init();
  lcd.writeLine("TEST", 4, 0);
}