#pragma once
#include "mmu.h"
#include "utils.h"

class CPU {
public:
  CPU(MMU &mmu) : mmu(mmu) {}
  int step();

private:
  Registers regs;
  MMU &mmu;
};
