#pragma once
#include "cpu.h"
#include "mmu.h"

class Debugger {
public:
  Debugger(CPU &cpu, MMU &mmu);

  void draw() const;
  void updateState();

private:
  CPU &cpu;
  MMU &mmu;

  void drawCPU() const;
};
