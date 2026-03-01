#include "../include/cpu.h"
#include <stdexcept>

CPU::CPU(MMU &mmu) : mmu(mmu) {};

uint8_t CPU::step() {
  // this is the step function
  return 4;
}

uint16_t CPU::getRegister(RegisterName name) {
  switch (name) {
  case RegisterName::AF:
    return this->regs.af;
  case RegisterName::BC:
    return this->regs.bc;
  case RegisterName::DE:
    return this->regs.de;
  case RegisterName::HL:
    return this->regs.hl;
  case RegisterName::SP:
    return this->regs.sp;
  case RegisterName::PC:
    return this->regs.pc;
  default:
    throw std::runtime_error("Invalid Register");
  }
}

bool CPU::getFlag(FlagName name) {
  switch (name) {
  case FlagName::Z:
    return this->regs.f.z;
  case FlagName::N:
    return this->regs.f.n;
  case FlagName::H:
    return this->regs.f.h;
  case FlagName::C:
    return this->regs.f.c;
  default:
    throw std::runtime_error("Invalid Flag");
  }
}
