#pragma once
#include <stdint.h>

struct Flags {
  uint8_t unused : 4;
  uint8_t c : 1;
  uint8_t h : 1;
  uint8_t n : 1;
  uint8_t z : 1;
};

struct Registers {
  union {
    struct {
      uint8_t a;
      Flags f;
    };
    uint16_t af = 0;
  };

  union {
    struct {
      uint8_t b;
      uint8_t c;
    };
    uint16_t bc = 0;
  };

  union {
    struct {
      uint8_t d;
      uint8_t e;
    };
    uint16_t de = 0;
  };

  union {
    struct {
      uint8_t h;
      uint8_t l;
    };
    uint16_t hl = 0;
  };

  uint16_t sp = 0;
  uint16_t pc = 0;
};

enum RegisterName { AF, BC, DE, HL, SP, PC };
enum FlagName { Z, N, H, C };
