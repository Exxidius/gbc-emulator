#pragma once
#include "mmu.h"
#include "utils.h"

class CPU {
public:
  struct OpCode {
    const char *name;
    uint8_t length;
    uint8_t cycles;
    uint8_t cycles_alt;
    void (CPU::*handler)();
  };

  CPUState state;
  static const OpCode opcode_table[256];
  static const OpCode cb_opcode_table[256];

  CPU(MMU &mmu);

  uint8_t step();
  uint16_t getRegister(RegisterName name);

  bool getFlag(uint8_t flagMask);
  void setFlag(uint8_t flagMask, bool condition);

private:
  Registers regs;
  MMU &mmu;

  void op_nop();
};
