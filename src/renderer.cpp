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

Context::Context(int width_win, int height_win, int width_tex, int height_tex) {
  window.reset(SDL_CreateWindow("Game Boy Color", width_win, height_win,
                                SDL_WINDOW_ALWAYS_ON_TOP));
  if (!window) {
    throw std::runtime_error("Failed to create window");
  }

  renderer.reset(SDL_CreateRenderer(window.get(), nullptr));
  if (!renderer) {
    throw std::runtime_error("Failed to create renderer");
  }

  texture.reset(SDL_CreateTexture(renderer.get(), SDL_PIXELFORMAT_RGBA8888,
                                  SDL_TEXTUREACCESS_STREAMING, width_tex,
                                  height_tex));
  if (!texture) {
    throw std::runtime_error("Failed to create texture");
  }
  SDL_SetTextureBlendMode(texture.get(), SDL_BLENDMODE_NONE);
  SDL_SetTextureScaleMode(texture.get(), SDL_SCALEMODE_NEAREST);
}

ImGuiSystem::ImGuiSystem(SDL_Window *w, SDL_Renderer *r) {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  ImGui::StyleColorsDark();
  ImGuiStyle &style = ImGui::GetStyle();
  style.Colors[ImGuiCol_TitleBg] = style.Colors[ImGuiCol_TitleBgActive];

  ImGui_ImplSDL3_InitForSDLRenderer(w, r);
  ImGui_ImplSDLRenderer3_Init(r);
}

ImGuiSystem::~ImGuiSystem() {
  ImGui_ImplSDLRenderer3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();
}

Renderer::Renderer(size_t width, size_t height)
    : texture_width(width * scale), texture_height(height * scale),
      display_width(texture_width + 2 * imgui_width + 4 * padding),
      display_height(texture_height + 2 * padding),
      ctx(display_width, display_height, texture_width / scale,
          texture_height / scale),
      imgui(ctx.window.get(), ctx.renderer.get()) {}

void Renderer::draw(const std::vector<uint32_t> &pixels) {
  SDL_UpdateTexture(ctx.texture.get(), nullptr, pixels.data(),
                    texture_width / scale * sizeof(uint32_t));

  ImGuiWindowFlags window_flags =
      ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
  ImGui_ImplSDLRenderer3_NewFrame();
  ImGui_ImplSDL3_NewFrame();
  ImGui::NewFrame();

  ImGui::SetNextWindowPos(ImVec2(padding, padding));
  ImGui::SetNextWindowSize(ImVec2(imgui_width, texture_height),
                           ImGuiCond_Appearing);
  ImGui::Begin("Debug Information", nullptr, window_flags);
  ImGui::Text("FPS: %f", ImGui::GetIO().Framerate);
  ImGui::End();

  ImGui::SetNextWindowPos(
      ImVec2(imgui_width + texture_width + 3 * padding, padding));
  ImGui::SetNextWindowSize(ImVec2(imgui_width, texture_height),
                           ImGuiCond_Appearing);
  ImGui::Begin("Controls", nullptr, window_flags);
  ImGui::End();

  SDL_FRect dest_rect = {float(imgui_width + 2 * padding), float(padding),
                         float(texture_width), float(texture_height)};
  SDL_RenderClear(ctx.renderer.get());
  SDL_RenderTexture(ctx.renderer.get(), ctx.texture.get(), nullptr, &dest_rect);
}

void Renderer::render() {
  ImGui::Render();
  ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(),
                                        ctx.renderer.get());

  SDL_RenderPresent(ctx.renderer.get());
}
