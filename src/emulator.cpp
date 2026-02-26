#include "../include/emulator.h"

void Emulator::run() {
  bool running = true;
  while (running) {
    running = inputhandler.processInput();

    this->cpu.step();

    this->renderer.draw(pixels, this->debugger);
    SDL_Delay(1000 / GB_FRAMERATE);
  }
}
