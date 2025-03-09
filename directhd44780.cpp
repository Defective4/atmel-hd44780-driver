#include "hd44780.cpp"
#include <avr/io.h>

class DirectHD44780 : public HD44780 {
  uint8_t pinRs, pinEn;
  uint8_t pinD4, pinD5, pinD6, pinD7;
public:
  DirectHD44780(uint8_t rs,
                uint8_t en,
                uint8_t d4,
                uint8_t d5,
                uint8_t d6,
                uint8_t d7) {
    pinRs = _BV(rs);
    pinEn = _BV(en);
    pinD4 = _BV(d4);
    pinD5 = _BV(d5);
    pinD6 = _BV(d6);
    pinD7 = _BV(d7);
    DDRB |= pinRs | pinEn;
    DDRC |= pinD4 | pinD5 | pinD6 | pinD7;
  }

  void write4Bit(uint8_t bits, bool mode) override {
    PORTB &= ~(pinRs | pinEn);
    PORTC &= ~(pinD4 | pinD5 | pinD6 | pinD7);

    if (mode) {
      PORTB |= pinRs;
    }

    if (bits & 0b1)
      PORTC |= pinD4;
    if (bits & 0b10)
      PORTC |= pinD5;
    if (bits & 0b100)
      PORTC |= pinD6;
    if (bits & 0b1000)
      PORTC |= pinD7;

    commit();
  }

  void commit() override {
    PORTB |= pinEn;
    sleep(5);
    PORTB &= ~pinEn;
  }
};