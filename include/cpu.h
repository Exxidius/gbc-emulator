#pragma once
#include "mmu.h"
#include "utils.h"

class CPU {
public:
  CPUState state;

  CPU(MMU &mmu);

  uint8_t step();
  uint16_t getRegister(RegisterName name);
  bool getFlag(FlagName name);

private:
  Registers regs;
  MMU &mmu;
};
