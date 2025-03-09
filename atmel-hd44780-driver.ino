#include "hd44780.cpp"
#ifndef F_CPU
#define F_CPU 1000000
#endif

int main(void) {
  DDRB = 0b00000011;
  DDRC = 0b00001111;
  HD44780 lcd(PB0, PB1, PC0, PC1, PC2, PC3);
  lcd.init();
}