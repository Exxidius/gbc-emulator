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
    std::string flagnames[6] = {"z", "n", "h", "c"};
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
