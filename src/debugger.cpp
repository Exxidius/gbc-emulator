#include "../include/debugger.h"
#include <string>

Debugger::Debugger(CPU &cpu, MMU &mmu) : cpu(cpu), mmu(mmu) {
  mem_edit.Cols = 8;
}

void Debugger::draw() {
  ImGui::Begin("Debug Information");
  if (ImGui::BeginTabBar("Components")) {
    if (ImGui::BeginTabItem("CPU")) {
      drawCPU();
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Memory")) {
      drawMemory();
      ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
  }
  ImGui::End();
}

void Debugger::drawMemory() {
  static uint8_t full_memory[0x10000];
  for (int i = 0; i < 0x10000; i++) {
    full_memory[i] = mmu.read(i);
  }

  mem_edit.DrawContents(full_memory, 0x10000);
}

void Debugger::drawCPU() const {
  ImGui::SeparatorText("Registers");
  if (ImGui::BeginTable("regs", 4)) {
    std::string regnames[6] = {"AF", "BC", "DE", "HL", "SP", "PC"};
    for (int curr = RegisterName::AF; curr <= RegisterName::PC / 2; curr++) {
      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      ImGui::Text("%s:", regnames[curr].c_str());
      ImGui::TableNextColumn();
      ImGui::Text("0x%X", cpu.getRegister(static_cast<RegisterName>(curr)));
      ImGui::TableNextColumn();
      ImGui::Text("%s:", regnames[curr + 3].c_str());
      ImGui::TableNextColumn();
      ImGui::Text("0x%X", cpu.getRegister(static_cast<RegisterName>(curr + 1)));
    }
    ImGui::EndTable();
  }

  ImGui::SeparatorText("Flags");
  if (ImGui::BeginTable("flags", 4)) {
    std::string flagnames[4] = {"z", "n", "h", "c"};
    for (int curr = FlagName::Z; curr <= FlagName::C / 2; curr++) {
      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      ImGui::Text("%s:", flagnames[curr].c_str());
      ImGui::TableNextColumn();
      ImGui::Text("%d", cpu.getFlag(static_cast<FlagName>(curr)));
      ImGui::TableNextColumn();
      ImGui::Text("%s:", flagnames[curr + 2].c_str());
      ImGui::TableNextColumn();
      ImGui::Text("%d", cpu.getFlag(static_cast<FlagName>(curr + 2)));
    }
    ImGui::EndTable();
  }
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

  ImGui::SeparatorText("Gamepad");

  if (ImGui::BeginTable("gamepad_table", 2, ImGuiTableFlags_NoSavedSettings)) {
    ImGui::TableNextColumn();

    ImGui::Text("D-Pad");
    ImGui::Indent();
    ImGui::InvisibleButton("##up_space", ImVec2(30, 30));
    ImGui::SameLine();
    if (ImGui::Button("U", ImVec2(30, 30))) {
    }

    if (ImGui::Button("L", ImVec2(30, 30))) {
    }
    ImGui::SameLine();
    ImGui::Button(" ", ImVec2(30, 30));
    ImGui::SameLine();
    if (ImGui::Button("R", ImVec2(30, 30))) {
    }

    ImGui::InvisibleButton("##down_space", ImVec2(30, 30));
    ImGui::SameLine();
    if (ImGui::Button("D", ImVec2(30, 30))) {
    }
    ImGui::Unindent();

    ImGui::TableNextColumn();

    ImGui::Text("Actions");
    ImGui::Spacing();
    ImGui::Spacing();

    ImGui::Indent();
    if (ImGui::Button("B", ImVec2(40, 40))) {
    }
    ImGui::SameLine();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 10);
    if (ImGui::Button("A", ImVec2(40, 40))) {
    }
    ImGui::Unindent();

    ImGui::EndTable();
  }

  ImGui::Spacing();
  float windowWidth = ImGui::GetContentRegionAvail().x;
  if (ImGui::Button("Select", ImVec2(windowWidth * 0.486f, 20))) {
  }
  ImGui::SameLine();
  if (ImGui::Button("Start", ImVec2(windowWidth * 0.486f, 20))) {
  }

  if (ImGui::Button("Reset Emulator", ImVec2(-1.0f, 0))) {
  }
  if (ImGui::Button("Exit", ImVec2(-1.0f, 0))) {
    cpu.state.running = false;
  }
  ImGui::End();
}
