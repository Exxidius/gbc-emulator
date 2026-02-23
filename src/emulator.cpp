#include "../include/emulator.h"
#include <iostream>

void Emulator::Run() {
  bool running = true;
  while (running) {
    running = inputhandler.processInput();
    this->renderer.draw(pixels);
    SDL_Delay(1000.f / GB_FRAMERATE);
  }
}
