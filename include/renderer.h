#pragma once
#include <SDL3/SDL.h>
#include <memory>
#include <vector>

const int window_width = 1280;
const int window_height = 720;

struct SDLWindowDestroyer {
  inline void operator()(SDL_Window *w) const { SDL_DestroyWindow(w); }
};

struct SDLRendererDestroyer {
  inline void operator()(SDL_Renderer *r) const { SDL_DestroyRenderer(r); }
};

struct SDLTextureDestroyer {
  inline void operator()(SDL_Texture *t) const { SDL_DestroyTexture(t); }
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

  Context(int width, int height);
};

struct ImGuiSystem {
  ImGuiSystem(SDL_Window *w, SDL_Renderer *r);
  ~ImGuiSystem();
};

class Renderer {
  Context ctx;
  ImGuiSystem imgui;

  int display_width;
  int display_height;

public:
  Renderer(size_t width, size_t height);
  void draw(const std::vector<uint32_t> &pixels);
};
