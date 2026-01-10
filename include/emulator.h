#pragma once
#include "input_handler.h"
#include "renderer.h"
#include <vector>

const int GB_WIDTH = 160;
const int GB_HEIGHT = 144;

class Emulator {
  Renderer renderer = Renderer(GB_WIDTH, GB_HEIGHT);
  InputHandler inputhandler = InputHandler();

  std::vector<uint32_t> pixels =
      std::vector<uint32_t>(GB_WIDTH * GB_HEIGHT, 0xFF0000FF);

public:
  void run();
};
