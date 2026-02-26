#pragma once
#include "cpu.h"
#include "input_handler.h"
#include "mmu.h"
#include "renderer.h"
#include <vector>

using std::vector;

const int GB_WIDTH = 160;
const int GB_HEIGHT = 144;
const int GB_FRAMERATE = 60;
const uint32_t GB_GREEN = 0x9BBC0FFF;

class Emulator {
public:
  void run();

private:
  // Emulator Logic
  PPU ppu;
  APU apu;
  Cartridge cartridge;
  Timer timer;
  Joypad joypad;
  MMU mmu = MMU(ppu, cartridge, joypad, timer, apu);
  CPU cpu = CPU(mmu);

  // Human User Interface
  Renderer renderer = Renderer(GB_WIDTH, GB_HEIGHT);
  InputHandler inputhandler = InputHandler();
  Debugger debugger = Debugger(cpu, mmu);

  vector<uint32_t> pixels = vector<uint32_t>(GB_WIDTH * GB_HEIGHT, GB_GREEN);
};
