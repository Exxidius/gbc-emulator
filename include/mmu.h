#pragma once
#include "apu.h"
#include "cartridge.h"
#include "joypad.h"
#include "ppu.h"
#include "timer.h"
#include <stdint.h>
#include <vector>

class MMU {
public:
  MMU(PPU &ppu, Cartridge &cartridge, Joypad &joypad, Timer &timer, APU &apu);

  uint8_t read(uint16_t addr);
  uint8_t readIO(uint16_t addr);

  void write(uint16_t addr, uint8_t value);
  void writeIO(uint16_t addr, uint8_t value);

private:
  PPU &ppu;
  Cartridge &cartridge;
  Joypad &joypad;
  Timer &timer;
  APU &apu;

  std::vector<uint8_t> wram = std::vector<uint8_t>(0x2000, 0);
  std::vector<uint8_t> hram = std::vector<uint8_t>(0x7E, 0);
  uint8_t interrupt_register = 0;
};
