cmake_minimum_required(VERSION 3.2...4.0)

project(GBemulator)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL3 REQUIRED)

# TODO: Outsource to static library later
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/thirdparty/imgui")
set(THIRDPARTY_DIR "${CMAKE_SOURCE_DIR}/thirdparty")
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer3.cpp
)

set(EMULATOR_SOURCES
    src/main.cpp
    src/mmu.cpp
    src/ppu.cpp
    src/cartridge.cpp
    src/emulator.cpp
    src/cpu.cpp
    src/renderer.cpp
    src/input_handler.cpp
    src/debugger.cpp
    src/timer.cpp
)

add_executable(
    GBemulator
    ${EMULATOR_SOURCES}
    ${IMGUI_SOURCES}
)

target_include_directories(GBemulator PRIVATE
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${THIRDPARTY_DIR}
)

target_link_libraries(GBemulator PRIVATE SDL3::SDL3)
