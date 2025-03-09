#import <avr/io.h>

class M74HC595 {
  uint8_t serial, sclock, slatch;

  void commit() {
    PORTC |= slatch;
    PORTC &= ~slatch;
  }

public:
  M74HC595(uint8_t serial, uint8_t sclock, uint8_t slatch) {
    this->serial = _BV(serial);
    this->sclock = _BV(sclock);
    this->slatch = _BV(slatch);

    DDRC |= this->serial | this->sclock | this->slatch;
  }

  void setByte(uint8_t byte) {
    for (int i = 0; i < 8; i++) {
      PORTC = 0;
      if (byte >> i & 0b1) {
        PORTC |= serial;
      }
      PORTC |= sclock;
    }
    PORTC = 0;
    commit();
  }
};