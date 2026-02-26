#include "../include/cartridge.h"

uint8_t Cartridge::readROM(uint16_t addr) { return 0xFF; }

uint8_t Cartridge::readExtRAM(uint16_t addr) { return 0xFF; }

void Cartridge::writeExtRAM(uint16_t addr, uint8_t value) {}
