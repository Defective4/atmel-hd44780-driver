#include <avr/io.h>
#include <util/delay_basic.h>
#ifndef F_CPU
#define F_CPU 1000000
#endif

class HD44780 {
  uint8_t pinRs, pinEn;
  uint8_t pinD4, pinD5, pinD6, pinD7;

  void writeString(char* str, int len) {
    for (int i = 0; i < len; i++)
      writeChar(str[i]);
  }

  void writeByte(uint8_t byte, bool mode) {
    write4Bit((byte >> 4) & 0x0f, mode);
    write4Bit(byte & 0x0f, mode);
  }

  void write4Bit(uint8_t bits, bool mode) {
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

  void commit() {
    PORTB |= pinEn;
    sleep(5);
    PORTB &= ~pinEn;
  }

public:
  HD44780(uint8_t rs,
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
  }

  void init() {
    sleep(10);
    write4Bit(0b0010, false);
    clearDisplay();
    writeByte(0b00101000, false);
    writeByte(0b00001100, false);
    writeByte(0b00000110, false);
  }

  void clearDisplay() {
    writeByte(0b00000001, false);
  }

  void writeChar(char c) {
    writeByte(c, true);
  }

  void setLine(int line) {
    uint8_t hi = 0b10000000;
    if (line > 0)
      hi |= 0b01000000;
    writeByte(hi, false);
  }

  void writeLine(char* str, int len, int line) {
    setLine(line);
    writeString(str, len);
  }

  void createChar(int location, uint8_t lines[]) {
    uint8_t addr = 0b01000000;
    addr |= (location % 7) << 3;
    writeByte(addr, false);
    for (int i = 0; i < 8; i++) {
      writeByte(lines[i], true);
    }
  }

  void sleep(uint16_t ms) {
    _delay_loop_2(F_CPU / 4e3 * ms);
  }
};