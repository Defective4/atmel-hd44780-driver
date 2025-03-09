#include "hd44780_base.cpp"
#include "m74hc595.cpp"
#include <avr/io.h>

class ShiftRegHD44780 : public HD44780 {
public:

  M74HC595* reg;

  ShiftRegHD44780(uint8_t serial, uint8_t sclock, uint8_t slatch) {
    this->reg = new M74HC595(serial, sclock, slatch);
  }

  uint8_t lastbits;

  void standby() {
    reg->setByte(0);
  }

  void write4Bit(uint8_t bits, bool mode) override {
    standby();
    uint8_t bs = bits << 2;
    if (mode) {
      bs |= 0b1;
    }
    lastbits = bs;
    reg->setByte(bs);

    commit();
  }

  void commit() override {
    reg->setByte(lastbits | 0b10);
    sleep100us();
    reg->setByte(lastbits & ~0b10);
  }
};