#include "../include/emulator.h"

void Emulator::run() {
  while (cpu.state.running) {
    cpu.state.running = inputhandler.processInput();

    if (!cpu.state.paused) {
      uint8_t cycles = this->cpu.step();

      if (cpu.state.step_mode) {
        cpu.state.paused = true;
      }
    }

    this->renderer.draw(pixels);
    this->debugger.draw();
    this->debugger.updateState();
    this->renderer.render();
    SDL_Delay(1000.f / GB_FRAMERATE);
  }
}
