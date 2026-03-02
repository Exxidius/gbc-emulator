#pragma once
#include "cpu.h"
#include <stdint.h>

constexpr uint8_t FLAG_Z = 1 << 7;
constexpr uint8_t FLAG_N = 1 << 6;
constexpr uint8_t FLAG_H = 1 << 5;
constexpr uint8_t FLAG_C = 1 << 4;

struct Registers {
  union {
    struct {
      uint8_t f;
      uint8_t a;
    };
    uint16_t af = 0x01B0;
  };

  union {
    struct {
      uint8_t c;
      uint8_t b;
    };
    uint16_t bc = 0x0013;
  };

  union {
    struct {
      uint8_t e;
      uint8_t d;
    };
    uint16_t de = 0x00D8;
  };

  union {
    struct {
      uint8_t l;
      uint8_t h;
    };
    uint16_t hl = 0x014D;
  };

  uint16_t sp = 0xFFFE;
  uint16_t pc = 0x0100;
};

enum RegisterName { AF, BC, DE, HL, SP, PC };

struct CPUState {
  bool running = true;
  bool paused = true;
  bool step_mode = false;
};
