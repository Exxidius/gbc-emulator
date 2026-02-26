#pragma once
#include "debugger.h"
#include <SDL3/SDL.h>
#include <memory>
#include <vector>

struct SDLWindowDestroyer {
  void operator()(SDL_Window *w) const { SDL_DestroyWindow(w); }
};

struct SDLRendererDestroyer {
  void operator()(SDL_Renderer *r) const { SDL_DestroyRenderer(r); }
};

struct SDLTextureDestroyer {
  void operator()(SDL_Texture *t) const { SDL_DestroyTexture(t); }
};

struct SDLSystem {
  SDLSystem();
  ~SDLSystem();
};

struct Context {
  SDLSystem sys;

  std::unique_ptr<SDL_Window, SDLWindowDestroyer> window;
  std::unique_ptr<SDL_Renderer, SDLRendererDestroyer> renderer;
  std::unique_ptr<SDL_Texture, SDLTextureDestroyer> texture;

  Context(int width_win, int height_win, int width_tex, int height_tex);
};

struct ImGuiSystem {
  ImGuiSystem(SDL_Window *w, SDL_Renderer *r);
  ~ImGuiSystem();
};

class Renderer {
  const int scale = 4;
  const int padding = 5;
  const int imgui_width = 150;
  int texture_width;
  int texture_height;
  int display_width;
  int display_height;

  Context ctx;
  ImGuiSystem imgui;

public:
  Renderer(size_t width, size_t height);
  void draw(const std::vector<uint32_t> &pixels, const Debugger &debugger);
};
