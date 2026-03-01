#pragma once
#include "constants.h"
#include "cpu.h"
#include "input_handler.h"
#include "mmu.h"
#include "renderer.h"

class Emulator {
public:
  void run();

private:
  // Emulator Logic
  PPU ppu;
  APU apu;
  Cartridge cartridge = Cartridge("../roms/test.gb");
  Timer timer;
  Joypad joypad;
  MMU mmu = MMU(ppu, cartridge, joypad, timer, apu);
  CPU cpu = CPU(mmu);

  // Human User Interface
  Renderer renderer = Renderer(GB_WIDTH, GB_HEIGHT);
  InputHandler inputhandler = InputHandler();
  Debugger debugger = Debugger(cpu, mmu);
};
