#include "../include/cpu.h"
#include <stdexcept>

CPU::CPU(MMU &mmu) : mmu(mmu) {};

uint8_t CPU::step() {
  uint8_t op = mmu.read(regs.pc++);
  const OpCode &instr = opcodes[op];

  if (instr.handler) {
    instr.handler();
  } else {
    throw std::runtime_error("Unimplemented opcode: " + std::to_string(op));
  }

  // Increase pc with instruction length - opcode byte
  regs.pc += instr.length - 1;
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

void CPU::initOpCodeTable() {
  opcodes[0x00] = {"NOP", 1, 4, 0, [this] { op_nop(); }};
  opcodes[0x01] = {"LD BC, imm16", 3, 12, 0,
                   [this] { op_ld_r16_imm16(regs.bc); }};
  opcodes[0x02] = {"LD [BC], A", 1, 8, 0, [this] { op_ld_r16mem_a(regs.bc); }};
  opcodes[0x03] = {"INC BC", 1, 8, 0, [this] { op_inc_r16(regs.bc); }};
  opcodes[0x04] = {"INC B", 1, 4, 0, [this] { op_inc_r8(regs.b); }};
  opcodes[0x05] = {"DEC B", 1, 4, 0, [this] { op_dec_r8(regs.b); }};
  opcodes[0x06] = {"LD B, imm8", 2, 8, 0, [this] { op_ld_r8_imm8(regs.b); }};
}

void CPU::op_nop() {}

void CPU::op_ld_r16_imm16(uint16_t &reg) {
  uint16_t val = mmu.read(regs.pc + 1) << 8 | mmu.read(regs.pc);
  reg = val;
}

void CPU::op_ld_r16mem_a(uint16_t addr) { mmu.write(addr, regs.a); }

void CPU::op_ld_a_r16mem(uint16_t addr) { regs.a = mmu.read(addr); }

void CPU::op_ld_imm16mem_sp(uint16_t addr) {
  mmu.write(addr, regs.sp & 0xff);
  mmu.write(addr + 1, regs.sp >> 8);
}

void CPU::op_inc_r16(uint16_t &reg) { reg++; }

void CPU::op_dec_r16(uint16_t &reg) { reg--; }

void CPU::op_add_hl_r16(uint16_t &reg) { regs.hl = reg; }

void CPU::op_inc_r8(uint8_t &reg) {
  uint8_t result = reg + 1;
  setFlag(FLAG_Z, result == 0);
  setFlag(FLAG_H, (reg & 0x0F) == 0x0F);
  setFlag(FLAG_N, 0);
  reg = result;
}

void CPU::op_dec_r8(uint8_t &reg) {
  uint8_t original = reg;
  reg--;
  setFlag(FLAG_Z, reg == 0);
  setFlag(FLAG_H, (original & 0x0F) == 0x0);
  setFlag(FLAG_N, 1);
}

void CPU::op_ld_r8_imm8(uint8_t &reg) { reg = mmu.read(regs.pc); }

void CPU::op_rlca() {
  bool msb = (regs.a >> 7) & 1;
  setFlag(FLAG_H, 0);
  setFlag(FLAG_Z, 0);
  setFlag(FLAG_N, 0);
  setFlag(FLAG_C, msb);
  regs.a <<= 1;
  regs.a |= msb;
}

void CPU::op_rrca() {}

void CPU::op_rla() {}

void CPU::op_rra() {}

void CPU::op_daa() {}

void CPU::op_cpl() {}

void CPU::op_scf() {}

void CPU::op_ccf() {}

void CPU::op_jr_imm8() {}

void CPU::op_jr_cond_imm8() {}

void CPU::op_stop() {}

void CPU::op_ld_r8_r8() {}

void CPU::op_halt() {}

void CPU::op_add_a_r8() {}

void CPU::op_adc_a_r8() {}

void CPU::op_sub_a_r8() {}

void CPU::op_sbc_a_r8() {}

void CPU::op_and_a_r8() {}

void CPU::op_xor_a_r8() {}

void CPU::op_or_a_r8() {}

void CPU::op_cp_a_r8() {}

void CPU::op_add_a_imm8() {}

void CPU::op_adc_a_imm8() {}

void CPU::op_sub_a_imm8() {}

void CPU::op_sbc_a_imm8() {}

void CPU::op_and_a_imm8() {}

void CPU::op_xor_a_imm8() {}

void CPU::op_or_a_imm8() {}

void CPU::op_cp_a_imm8() {}

void CPU::op_ret_cond() {}

void CPU::op_ret() {}

void CPU::op_reti() {}

void CPU::op_jp_cond_imm16() {}

void CPU::op_jp_imm16() {}

void CPU::op_jp_hl() {}

void CPU::op_call_cond_imm16() {}

void CPU::op_call_imm16() {}

void CPU::op_rst_tgt3() {}

void CPU::op_pop_r16stk() {}

void CPU::op_push_r16stk() {}

void CPU::op_ldh_c_a() {}

void CPU::op_ldh_imm8_a() {}

void CPU::op_ld_imm16_a() {}

void CPU::op_ldh_a_c() {}

void CPU::op_ldh_a_imm8() {}

void CPU::op_ld_a_imm16() {}

void CPU::op_add_sp_imm8() {}

void CPU::op_ld_hl_sp_imm8() {}

void CPU::op_ld_sp_hl() {}

void CPU::CPU::op_di() {}

void CPU::CPU::op_ei() {}
