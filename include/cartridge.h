#pragma once
#include <stdint.h>
#include <vector>

class Cartridge {
public:
  uint8_t readROM(uint16_t addr);
  uint8_t readExtRAM(uint16_t addr);

  void writeExtRAM(uint16_t addr, uint8_t value);

private:
  std::vector<uint8_t> rom = std::vector<uint8_t>();
  std::vector<uint8_t> ext_ram = std::vector<uint8_t>(0x2000, 0);
};
