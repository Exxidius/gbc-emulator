#pragma once
#include "cpu.h"
#include "input_handler.h"
#include "renderer.h"
#include <vector>

using std::vector;

const int GB_WIDTH = 160;
const int GB_HEIGHT = 144;
const int GB_FRAMERATE = 60;
const uint32_t GB_GREEN = 0x9BBC0FFF;

class Emulator {
  CPU cpu;
  Renderer renderer = Renderer(GB_WIDTH, GB_HEIGHT);
  InputHandler inputhandler = InputHandler();

  vector<uint32_t> pixels = vector<uint32_t>(GB_WIDTH * GB_HEIGHT, GB_GREEN);

public:
  void Run();
};
