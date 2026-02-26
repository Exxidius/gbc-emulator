#include "../include/mmu.h"

MMU::MMU(PPU &ppu, Cartridge &cartridge, Joypad &joypad, Timer &timer, APU &apu)
    : ppu(ppu), cartridge(cartridge), joypad(joypad), timer(timer), apu(apu) {}

uint8_t MMU::read(uint16_t addr) { return 0; }

void MMU::write(uint16_t addr, uint8_t value) {}
