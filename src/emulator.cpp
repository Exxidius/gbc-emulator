#include "../include/emulator.h"

void Emulator::run() {
  const uint64_t target_frame_time_ns = 1'000'000'000ULL / GB_FRAMERATE;
  const uint64_t sleep_margin_ns = 2'000'000ULL;

  while (cpu.state.running) {
    uint64_t frame_start_time = SDL_GetTicksNS();
    uint64_t target_end_time = frame_start_time + target_frame_time_ns;
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

    uint64_t frame_end_time = SDL_GetTicksNS();
    while (true) {
      uint64_t current_time = SDL_GetTicksNS();
      if (current_time >= target_end_time) {
        break;
      }

      uint64_t remaining_ns = target_end_time - current_time;

      if (remaining_ns > sleep_margin_ns) {
        SDL_DelayNS(remaining_ns - sleep_margin_ns);
      }
    }
  }
}
