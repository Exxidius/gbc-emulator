#pragma once
#include "apu.h"
#include "cartridge.h"
#include "joypad.h"
#include "ppu.h"
#include "timer.h"
#include <stdint.h>

class MMU {
public:
  MMU(PPU &ppu, Cartridge &cartridge, Joypad &joypad, Timer &timer, APU &apu);

  uint8_t read(uint16_t addr);
  void write(uint16_t addr, uint8_t value);

private:
  PPU &ppu;
  Cartridge &cartridge;
  Joypad &joypad;
  Timer &timer;
  APU &apu;
};
