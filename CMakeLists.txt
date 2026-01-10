cmake_minimum_required(VERSION 4.0)

project(gbc)

set(CMAKE_CXX_STANDARD 23)

find_package(SDL3 REQUIRED)

# TODO: Outsource to static library later
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/thirdparty/imgui")
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer3.cpp
)

add_executable(
    gbc
    src/main.cpp
    src/emulator.cpp
    src/renderer.cpp
    src/input_handler.cpp
    ${IMGUI_SOURCES}
)

target_include_directories(gbc PRIVATE
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

target_link_libraries(gbc PRIVATE SDL3::SDL3)
