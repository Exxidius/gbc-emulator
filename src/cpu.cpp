#include "../include/cpu.h"
#include <stdexcept>

CPU::CPU(MMU &mmu) : mmu(mmu) {};

uint8_t CPU::step() {
  uint8_t op = mmu.read(regs.pc);
  const OpCode &instr = opcodes[op];

  if (instr.handler) {
    instr.handler();
  } else {
    throw std::runtime_error("Unimplemented opcode: " + std::to_string(op));
  }

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

void CPU::initOpCodeTable() {
  opcodes[0x00] = {"NOP", 1, 4, 0, [this] { op_nop(); }};
  opcodes[0x01] = {"LD BC, imm16", 3, 12, 0, [this] { op_ld_r16_imm16(); }};
}

void CPU::op_nop() {}

void CPU::op_ld_r16_imm16() {}

void CPU::op_ld_r16mem_a() {}

void CPU::op_ld_a_r16mem() {}

void CPU::op_ld_imm16mem_sp() {}

void CPU::op_inc_r16() {}

void CPU::op_dec_r16() {}

void CPU::op_add_hl_r16() {}

void CPU::op_inc_r8() {}

void CPU::op_dec_r8() {}

void CPU::op_ld_r8_imm8() {}

void CPU::op_rlca() {}

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
