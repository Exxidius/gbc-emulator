#include "../include/debugger.h"
#include "imgui.h"
#include <string>

Debugger::Debugger(CPU &cpu, MMU &mmu) : cpu(cpu), mmu(mmu) {}

void Debugger::draw() const {
  ImGui::Begin("Debug Information");
  if (ImGui::BeginTabBar("Components")) {
    if (ImGui::BeginTabItem("CPU")) {
      drawCPU();
      ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
  }
  ImGui::End();
}

void Debugger::drawCPU() const {
  ImGui::Text("Registers");
  if (ImGui::BeginTable("regs", 2)) {
    std::string regnames[6] = {"AF", "BC", "DE", "HL", "SP", "PC"};
    for (int curr = RegisterName::AF; curr <= RegisterName::PC; curr++) {
      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      ImGui::Text("%s", regnames[curr].c_str());
      ImGui::TableNextColumn();
      ImGui::Text("0x%X", cpu.getRegister(static_cast<RegisterName>(curr)));
    }
    ImGui::EndTable();
  }
  ImGui::Separator();

  ImGui::Text("Flags");
  if (ImGui::BeginTable("flags", 2)) {
    std::string flagnames[4] = {"z", "n", "h", "c"};
    for (int curr = FlagName::Z; curr <= FlagName::C; curr++) {
      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      ImGui::Text("%s", flagnames[curr].c_str());
      ImGui::TableNextColumn();
      ImGui::Text("%d", cpu.getFlag(static_cast<FlagName>(curr)));
    }
    ImGui::EndTable();
  }
  ImGui::Separator();
}

void Debugger::updateState() {
  ImGui::Begin("Controls");
  std::string label = "";
  if (cpu.state.paused && cpu.state.step_mode) {
    label = "Step";
  } else if (cpu.state.paused) {
    label = "Resume";
  } else {
    label = "Pause";
  }
  if (ImGui::Button(label.c_str(), ImVec2(-1.0f, 0))) {
    cpu.state.paused = !cpu.state.paused;
  }
  if (ImGui::Button(cpu.state.step_mode ? "Exit Step Mode" : "Enter Step Mode",
                    ImVec2(-1.0f, 0))) {
    cpu.state.step_mode = !cpu.state.step_mode;
    cpu.state.paused = true;
  }
  ImGui::End();
}
