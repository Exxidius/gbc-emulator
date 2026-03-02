#include "../include/cartridge.h"
#include <fstream>

Cartridge::Cartridge(std::string romfile) {
  this->romfile = romfile;
  load();
}

uint8_t Cartridge::readROM(uint16_t addr) {
  if (addr >= rom.size()) {
    return 0xFF;
  }
  return rom.at(addr);
}

uint8_t Cartridge::readExtRAM(uint16_t addr) {
  if (addr >= ext_ram.size()) {
    return 0xFF;
  }
  return ext_ram.at(addr);
}

void Cartridge::writeExtRAM(uint16_t addr, uint8_t value) {
  if (addr >= ext_ram.size()) {
    return;
  }
  ext_ram.at(addr) = value;
}

void Cartridge::load() {
  std::ifstream file(romfile, std::ios::binary | std::ios::ate);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open ROM file");
  }
  int size = file.tellg();
  file.seekg(0, file.beg);
  rom.resize(size);
  file.read((char *)rom.data(), size);
}
