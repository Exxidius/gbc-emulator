#include "../include/mmu.h"

MMU::MMU(PPU &ppu, Cartridge &cartridge, Joypad &joypad, Timer &timer, APU &apu)
    : ppu(ppu), cartridge(cartridge), joypad(joypad), timer(timer), apu(apu) {}

uint8_t MMU::read(uint16_t addr) {
  if (addr <= 0x7FFF) {
    return cartridge.readROM(addr);
  }
  if (addr <= 0x9FFF) {
    return ppu.readVRAM(addr - 0x8000);
  }
  if (addr <= 0xBFFF) {
    return cartridge.readExtRAM(addr - 0xA000);
  }
  if (addr <= 0xDFFF) {
    return wram.at(addr - 0xC000);
  }
  if (addr <= 0xFDFF) {
    return this->read(addr - 0x2000);
  }
  if (addr <= 0XFE9F) {
    return ppu.readOAM(addr - 0xFE00);
  }
  if (addr <= 0xFEFF) {
    return 0xFF;
  }
  if (addr <= 0xFF7F) {
    this->readIO(addr);
  }
  if (addr <= 0xFFFE) {
    return hram.at(addr - 0xFF80);
  }
  if (addr == 0xFFFF) {
    return interrupt_register;
  }
  return 0xFF;
}

uint8_t MMU::readIO(uint16_t addr) { return 0xFF; }

void MMU::write(uint16_t addr, uint8_t value) {
  if (addr <= 0x7FFF) {
    return;
  }
  if (addr <= 0x9FFF) {
    ppu.writeVRAM(addr - 0x8000, value);
  }
  if (addr <= 0xBFFF) {
    cartridge.writeExtRAM(addr - 0xA000, value);
  }
  if (addr <= 0xDFFF) {
    wram.at(addr - 0xC000) = value;
  }
  if (addr <= 0xFDFF) {
    this->write(addr - 0x2000, value);
  }
  if (addr <= 0XFE9F) {
    ppu.writeOAM(addr - 0xFE00, value);
  }
  if (addr <= 0xFEFF) {
    return;
  }
  if (addr <= 0xFF7F) {
    this->writeIO(addr, value);
  }
  if (addr <= 0xFFFE) {
    hram.at(addr - 0xFF80) = value;
  }
  if (addr == 0xFFFF) {
    interrupt_register = value;
  }
}

void MMU::writeIO(uint16_t addr, uint8_t value) {}
