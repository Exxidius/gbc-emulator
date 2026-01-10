#include "../include/input_handler.h"
#include "imgui_impl_sdl3.h"
#include <SDL3/SDL.h>

bool InputHandler::processInput() {

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    ImGui_ImplSDL3_ProcessEvent(&event);
    if (event.type == SDL_EVENT_QUIT) {
      return false;
    }
  }
  return true;
}
