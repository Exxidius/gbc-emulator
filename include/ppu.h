#pragma once
#include <stdint.h>
#include <vector>

class PPU {
public:
  uint8_t readVRAM(uint16_t addr);
  uint8_t readOAM(uint16_t addr);

  void writeVRAM(uint16_t addr, uint8_t value);
  void writeOAM(uint16_t addr, uint8_t value);

private:
  std::vector<uint8_t> vram = std::vector<uint8_t>(0x2000, 0);
  std::vector<uint8_t> oam = std::vector<uint8_t>(0x9F, 0);
};
