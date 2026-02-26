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
    uint16_t af;
  };

  union {
    struct {
      uint8_t b;
      uint8_t c;
    };
    uint16_t bc;
  };

  union {
    struct {
      uint8_t d;
      uint8_t e;
    };
    uint16_t de;
  };

  union {
    struct {
      uint8_t h;
      uint8_t l;
    };
    uint16_t hl;
  };

  uint16_t sp;
  uint16_t pc;
};
