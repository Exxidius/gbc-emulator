#include "../include/emulator.h"

void Emulator::run() {

  bool running = true;
  while (running) {
    running = inputhandler.processInput();

    for (auto &p : pixels) {
      p = (rand() % 0xFF000000) | 0xFF;
    }

    this->renderer.draw(pixels);
  }
}
