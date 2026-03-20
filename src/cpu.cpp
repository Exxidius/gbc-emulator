#include "../include/cpu.h"
#include <stdexcept>

CPU::CPU(MMU &mmu) : mmu(mmu) {};

uint8_t CPU::step() {
  uint8_t op = mmu.read(regs.pc++);
  const OpCode &instr = opcodes[op];
  uint8_t cycles = instr.cycles;

  if (instr.handler) {
    if (instr.handler()) {
      cycles = instr.cycles_alt;
    }
  } else {
    throw std::runtime_error("Unimplemented opcode: " + std::to_string(op));
  }
  // return cycles;
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

bool CPU::getFlag(uint8_t flagMask) { return regs.f & flagMask; }

void CPU::setFlag(uint8_t flagMask, bool condition) {
  if (condition) {
    regs.f |= flagMask;
  } else {
    regs.f &= ~flagMask;
  }
}

uint8_t CPU::fetchByte() { return mmu.read(regs.pc++); }

uint16_t CPU::fetchWord() {
  uint8_t lo = fetchByte();
  uint8_t hi = fetchByte();
  return (hi << 8) | lo;
}

void CPU::initOpCodeTable() {
  opcodes[0x00] = {"NOP", 1, 4, 0, [this] { return op_nop(); }};
  opcodes[0x01] = {"LD BC, imm16", 3, 12, 0,
                   [this] { return op_ld_r16_imm16(regs.bc); }};
  opcodes[0x02] = {"LD [BC], A", 1, 8, 0,
                   [this] { return op_ld_r16mem_a(regs.bc); }};
  opcodes[0x03] = {"INC BC", 1, 8, 0, [this] { return op_inc_r16(regs.bc); }};
  opcodes[0x04] = {"INC B", 1, 4, 0, [this] { return op_inc_r8(regs.b); }};
  opcodes[0x05] = {"DEC B", 1, 4, 0, [this] { return op_dec_r8(regs.b); }};
  opcodes[0x06] = {"LD B, imm8", 2, 8, 0,
                   [this] { return op_ld_r8_imm8(regs.b); }};
  opcodes[0x07] = {"RLCA", 1, 4, 0, [this] { return op_rlca(); }};
  opcodes[0x08] = {"LD [imm16], SP", 3, 20, 0,
                   [this] { return op_ld_imm16mem_sp(fetchWord()); }};
  opcodes[0x09] = {"ADD HL, BC", 1, 8, 0,
                   [this] { return op_add_hl_r16(regs.bc); }};
  opcodes[0x0A] = {"LD A, [BC]", 1, 8, 0,
                   [this] { return op_ld_a_r16mem(regs.bc); }};
  opcodes[0x0B] = {"DEC BC", 1, 8, 0, [this] { return op_dec_r16(regs.bc); }};
  opcodes[0x0C] = {"INC C", 1, 4, 0, [this] { return op_inc_r8(regs.c); }};
  opcodes[0x0D] = {"DEC C", 1, 4, 0, [this] { return op_dec_r8(regs.c); }};
  opcodes[0x0E] = {"LD C, imm8", 2, 8, 0,
                   [this] { return op_ld_r8_imm8(regs.c); }};
  opcodes[0x0F] = {"RRCA", 1, 4, 0, [this] { return op_rrca(); }};

  opcodes[0x10] = {"STOP imm8", 2, 4, 0, [this] { return op_stop(); }};
  opcodes[0x11] = {"LD DE, imm16", 3, 12, 0,
                   [this] { return op_ld_r16_imm16(regs.de); }};
  opcodes[0x12] = {"LD [DE], A", 1, 8, 0,
                   [this] { return op_ld_r16mem_a(regs.de); }};
  opcodes[0x13] = {"INC DE", 1, 8, 0, [this] { return op_inc_r16(regs.de); }};
  opcodes[0x14] = {"INC D", 1, 4, 0, [this] { return op_inc_r8(regs.d); }};
  opcodes[0x15] = {"DEC D", 1, 4, 0, [this] { return op_dec_r8(regs.d); }};
  opcodes[0x16] = {"LD D, imm8", 2, 8, 0,
                   [this] { return op_ld_r8_imm8(regs.d); }};
  opcodes[0x17] = {"RLA", 1, 4, 0, [this] { return op_rla(); }};
  opcodes[0x18] = {"JR e8", 2, 12, 0, [this] { return op_jr_imm8(); }};
  opcodes[0x19] = {"ADD HL, DE", 1, 8, 0,
                   [this] { return op_add_hl_r16(regs.de); }};
  opcodes[0x1A] = {"LD A, [DE]", 1, 8, 0,
                   [this] { return op_ld_a_r16mem(regs.de); }};
  opcodes[0x1B] = {"DEC DE", 1, 8, 0, [this] { return op_dec_r16(regs.de); }};
  opcodes[0x1C] = {"INC E", 1, 4, 0, [this] { return op_inc_r8(regs.e); }};
  opcodes[0x1D] = {"DEC E", 1, 4, 0, [this] { return op_dec_r8(regs.e); }};
  opcodes[0x1E] = {"LD E, imm8", 2, 8, 0,
                   [this] { return op_ld_r8_imm8(regs.e); }};
  opcodes[0x1F] = {"RRA", 1, 4, 0, [this] { return op_rra(); }};
  opcodes[0x20] = {"JR NZ, e8", 2, 12, 8, [this] { return op_jr_cond_imm8(); }};
  opcodes[0x21] = {"LD HL, imm16", 3, 12, 0,
                   [this] { return op_ld_r16_imm16(regs.hl); }};
  opcodes[0x22] = {"LD [HL+], A", 1, 8, 0, [this] {
                     bool cond = op_ld_r16mem_a(regs.hl);
                     regs.hl++;
                     return cond;
                   }};
  opcodes[0x23] = {"INC HL", 1, 8, 0, [this] { return op_inc_r16(regs.hl); }};
  opcodes[0x24] = {"INC H", 1, 4, 0, [this] { return op_inc_r8(regs.h); }};
  opcodes[0x25] = {"DEC H", 1, 4, 0, [this] { return op_dec_r8(regs.h); }};
  opcodes[0x26] = {"LD H, imm8", 2, 8, 0,
                   [this] { return op_ld_r8_imm8(regs.h); }};
}

bool CPU::op_nop() { return false; }

bool CPU::op_ld_r16_imm16(uint16_t &reg) {
  reg = fetchWord();
  return false;
}

bool CPU::op_ld_r16mem_a(uint16_t addr) {
  mmu.write(addr, regs.a);
  return false;
}

bool CPU::op_ld_a_r16mem(uint16_t addr) {
  regs.a = mmu.read(addr);
  return false;
}

bool CPU::op_ld_imm16mem_sp(uint16_t addr) {
  mmu.write(addr, regs.sp & 0xff);
  mmu.write(addr + 1, regs.sp >> 8);
  return false;
}

bool CPU::op_inc_r16(uint16_t &reg) {
  reg++;
  return false;
}

bool CPU::op_dec_r16(uint16_t &reg) {
  reg--;
  return false;
}

bool CPU::op_add_hl_r16(uint16_t &reg) {
  uint16_t original = regs.hl;
  uint32_t result = regs.hl + reg;
  regs.hl = result & 0xFFFF;
  setFlag(FLAG_N, 0);
  setFlag(FLAG_C, result > 0xFFFF);
  setFlag(FLAG_H, ((original & 0x0FFF) + (reg & 0x0FFF)) > 0x0FFF);
  return false;
}

bool CPU::op_inc_r8(uint8_t &reg) {
  uint8_t result = reg + 1;
  setFlag(FLAG_Z, result == 0);
  setFlag(FLAG_H, (reg & 0x0F) == 0x0F);
  setFlag(FLAG_N, 0);
  reg = result;
  return false;
}

bool CPU::op_dec_r8(uint8_t &reg) {
  uint8_t original = reg;
  reg--;
  setFlag(FLAG_Z, reg == 0);
  setFlag(FLAG_H, (original & 0x0F) == 0x0);
  setFlag(FLAG_N, 1);
  return false;
}

bool CPU::op_ld_r8_imm8(uint8_t &reg) {
  reg = fetchByte();
  return false;
}

bool CPU::op_rlca() {
  bool msb = (regs.a >> 7) & 1;
  setFlag(FLAG_H, 0);
  setFlag(FLAG_Z, 0);
  setFlag(FLAG_N, 0);
  setFlag(FLAG_C, msb);
  regs.a <<= 1;
  regs.a |= msb;
  return false;
}

bool CPU::op_rrca() {
  bool lsb = regs.a & 1;
  setFlag(FLAG_H, 0);
  setFlag(FLAG_Z, 0);
  setFlag(FLAG_N, 0);
  setFlag(FLAG_C, lsb);
  regs.a >>= 1;
  regs.a |= (lsb << 7);
  return false;
}

bool CPU::op_rla() {
  bool old_c = getFlag(FLAG_C);
  setFlag(FLAG_H, 0);
  setFlag(FLAG_Z, 0);
  setFlag(FLAG_N, 0);
  setFlag(FLAG_C, (regs.a >> 7) & 1);
  regs.a <<= 1;
  regs.a |= old_c;
  return false;
}

bool CPU::op_rra() {
  bool old_c = getFlag(FLAG_C);
  setFlag(FLAG_H, 0);
  setFlag(FLAG_Z, 0);
  setFlag(FLAG_N, 0);
  setFlag(FLAG_C, regs.a & 1);
  regs.a >>= 1;
  regs.a |= (old_c << 7);
  return false;
}

bool CPU::op_daa() { return false; }

bool CPU::op_cpl() { return false; }

bool CPU::op_scf() { return false; }

bool CPU::op_ccf() { return false; }

bool CPU::op_jr_imm8() {
  uint8_t e8 = fetchByte();
  regs.pc += (int8_t)e8;
  return false;
}

bool CPU::op_jr_cond_imm8() {
  uint8_t e8 = fetchByte();
  bool nz = (getFlag(FLAG_Z) != 0);
  regs.pc += (int8_t)(nz ? e8 : 0);
  return nz;
}

bool CPU::op_stop() {
  fetchByte();
  // TODO: check if I need a new state here
  state.paused = true;
  return false;
}

bool CPU::op_ld_r8_r8() { return false; }

bool CPU::op_halt() { return false; }

bool CPU::op_add_a_r8() { return false; }

bool CPU::op_adc_a_r8() { return false; }

bool CPU::op_sub_a_r8() { return false; }

bool CPU::op_sbc_a_r8() { return false; }

bool CPU::op_and_a_r8() { return false; }

bool CPU::op_xor_a_r8() { return false; }

bool CPU::op_or_a_r8() { return false; }

bool CPU::op_cp_a_r8() { return false; }

bool CPU::op_add_a_imm8() { return false; }

bool CPU::op_adc_a_imm8() { return false; }

bool CPU::op_sub_a_imm8() { return false; }

bool CPU::op_sbc_a_imm8() { return false; }

bool CPU::op_and_a_imm8() { return false; }

bool CPU::op_xor_a_imm8() { return false; }

bool CPU::op_or_a_imm8() { return false; }

bool CPU::op_cp_a_imm8() { return false; }

bool CPU::op_ret_cond() { return false; }

bool CPU::op_ret() { return false; }

bool CPU::op_reti() { return false; }

bool CPU::op_jp_cond_imm16() { return false; }

bool CPU::op_jp_imm16() { return false; }

bool CPU::op_jp_hl() { return false; }

bool CPU::op_call_cond_imm16() { return false; }

bool CPU::op_call_imm16() { return false; }

bool CPU::op_rst_tgt3() { return false; }

bool CPU::op_pop_r16stk() { return false; }

bool CPU::op_push_r16stk() { return false; }

bool CPU::op_ldh_c_a() { return false; }

bool CPU::op_ldh_imm8_a() { return false; }

bool CPU::op_ld_imm16_a() { return false; }

bool CPU::op_ldh_a_c() { return false; }

bool CPU::op_ldh_a_imm8() { return false; }

bool CPU::op_ld_a_imm16() { return false; }

bool CPU::op_add_sp_imm8() { return false; }

bool CPU::op_ld_hl_sp_imm8() { return false; }

bool CPU::op_ld_sp_hl() { return false; }

bool CPU::CPU::op_di() { return false; }

bool CPU::CPU::op_ei() { return false; }
