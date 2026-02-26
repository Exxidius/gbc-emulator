#include "../include/emulator.h"

void Emulator::run() {
  bool running = true;
  while (running) {
    running = inputhandler.processInput();

    this->cpu.step();

    this->renderer.draw(pixels);
    SDL_Delay(1000.f / GB_FRAMERATE);
  }
}
