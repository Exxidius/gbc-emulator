#include "../include/renderer.h"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

SDLSystem::SDLSystem() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    throw std::runtime_error("Failed to init SDL");
  }
}

SDLSystem::~SDLSystem() { SDL_Quit(); }

Context::Context(int width, int height) {
  window.reset(
      SDL_CreateWindow("Game Boy Color", 1280, 720, SDL_WINDOW_ALWAYS_ON_TOP));
  if (!window) {
    throw std::runtime_error("Failed to create window");
  }

  renderer.reset(SDL_CreateRenderer(window.get(), NULL));
  if (!renderer) {
    throw std::runtime_error("Failed to create renderer");
  }

  texture.reset(SDL_CreateTexture(renderer.get(), SDL_PIXELFORMAT_RGBA32,
                                  SDL_TEXTUREACCESS_STREAMING, width, height));
  if (!texture) {
    throw std::runtime_error("Failed to create texture");
  }
}

ImGuiSystem::ImGuiSystem(SDL_Window *w, SDL_Renderer *r) {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  ImGui::StyleColorsDark();

  ImGui_ImplSDL3_InitForSDLRenderer(w, r);
  ImGui_ImplSDLRenderer3_Init(r);
}

ImGuiSystem::~ImGuiSystem() {
  ImGui_ImplSDLRenderer3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();
}

Renderer::Renderer(size_t width, size_t height)
    : display_width(width), display_height(height), ctx(width, height),
      imgui(ctx.window.get(), ctx.renderer.get()) {}

void Renderer::draw(const std::vector<uint32_t> &pixels) {
  SDL_UpdateTexture(ctx.texture.get(), nullptr, pixels.data(),
                    display_width * 4);

  ImGui_ImplSDLRenderer3_NewFrame();
  ImGui_ImplSDL3_NewFrame();
  ImGui::NewFrame();

  ImGui::Begin("Debugging Window");
  if (ImGui::Button("Step Instruction")) {
  }
  ImGui::End();

  SDL_RenderClear(ctx.renderer.get());
  SDL_RenderTexture(ctx.renderer.get(), ctx.texture.get(), nullptr, nullptr);

  ImGui::Render();
  ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(),
                                        ctx.renderer.get());

  SDL_RenderPresent(ctx.renderer.get());
}
