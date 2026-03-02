#include "../include/cpu.h"
#include <stdexcept>

CPU::CPU(MMU &mmu) : mmu(mmu){};

uint8_t CPU::step() {
  uint8_t op = mmu.read(regs.pc);
  const OpCode &instr = opcode_table[op];

  (this->*instr.handler)();

  regs.pc += instr.length;
  return 4; // swap with cycles later
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

bool CPU::getFlag(uint8_t flagMask) { return regs.f & flagMask; }

void CPU::setFlag(uint8_t flagMask, bool condition) {
  if (condition) {
    regs.f |= flagMask;
  } else {
    regs.f &= ~flagMask;
  }
}

void CPU::op_nop() {}

const CPU::OpCode CPU::opcode_table[256] = {
    {"NOP", 1, 4, 0, &CPU::op_nop},
    {"LD BC, d16", 3, 12, 0, &CPU::op_nop},
};

const CPU::OpCode CPU::cb_opcode_table[256] = {};
