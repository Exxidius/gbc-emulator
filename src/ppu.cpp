#include "../include/ppu.h"

uint8_t PPU::readVRAM(uint16_t addr) { return 0xFF; }
uint8_t PPU::readOAM(uint16_t addr) { return 0xFF; }

void PPU::writeVRAM(uint16_t addr, uint8_t value) {}
void PPU::writeOAM(uint16_t addr, uint8_t value) {}
