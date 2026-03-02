#pragma once
#include "constants.h"
#include <stdint.h>
#include <vector>

class PPU {
public:
  uint8_t readVRAM(uint16_t addr);
  uint8_t readOAM(uint16_t addr);

  void writeVRAM(uint16_t addr, uint8_t value);
  void writeOAM(uint16_t addr, uint8_t value);
  void tick(uint8_t cycles);

  std::vector<uint32_t> &getPixels();

private:
  std::vector<uint8_t> vram = std::vector<uint8_t>(0x2000, 0);
  std::vector<uint8_t> oam = std::vector<uint8_t>(0xA0, 0);
  std::vector<uint32_t> pixels =
      std::vector<uint32_t>(GB_WIDTH * GB_HEIGHT, GB_LIGHT_GREEN);
};
