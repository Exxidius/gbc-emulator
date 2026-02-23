#pragma once
#include <stdint.h>

enum class RegType16Bit {
  AF,
  BC,
  DE,
  HL,
  SP,
  PC,
};

enum class RegType8Bit {
  A,
  B,
  C,
  D,
  E,
  H,
  L,
};

enum class FlagType { z, n, h, c };

class CPU {
  uint16_t af = 0;
  uint16_t bc = 0;
  uint16_t de = 0;
  uint16_t hl = 0;

  uint16_t sp = 0;
  uint16_t pc = 0;

public:
  bool GetFlag(FlagType type);
  uint8_t GetReg8Bit(RegType8Bit type);
  uint16_t GetReg16Bit(RegType16Bit type);

  void SetFlag(FlagType type, bool value);
  void SetReg8Bit(RegType8Bit type, uint8_t value);
  void SetReg16Bit(RegType16Bit type, uint16_t value);
};
