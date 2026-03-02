#pragma once
#include "cpu.h"
#include "imgui.h"
#include "imgui_memory_editor.h"
#include "mmu.h"

class Debugger {
public:
  Debugger(CPU &cpu, MMU &mmu);

  void draw();
  void updateState();

private:
  CPU &cpu;
  MMU &mmu;

  MemoryEditor mem_edit;

  void drawCPU() const;
  void drawMemory();
  void drawDisassembly() const;
};
