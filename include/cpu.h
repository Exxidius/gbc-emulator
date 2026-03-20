#pragma once
#include "mmu.h"
#include "utils.h"
#include <functional>

class CPU {
public:
  struct OpCode {
    const char *name;
    uint8_t length;
    uint8_t cycles;
    uint8_t cycles_alt;
    std::function<bool()> handler;
  };

  CPUState state;
  OpCode opcodes[256];
  OpCode cbopcodes[256];

  CPU(MMU &mmu);

  uint8_t step();
  uint16_t getRegister(RegisterName name);

  bool getFlag(uint8_t flagMask);
  void setFlag(uint8_t flagMask, bool condition);

private:
  Registers regs;
  MMU &mmu;

  uint8_t fetchByte();
  uint16_t fetchWord();

  void initOpCodeTable();

  bool op_nop();

  bool op_ld_r16_imm16(uint16_t &reg);
  bool op_ld_r16mem_a(uint16_t addr);
  bool op_ld_a_r16mem(uint16_t addr);
  bool op_ld_imm16mem_sp(uint16_t addr);

  bool op_inc_r16(uint16_t &reg);
  bool op_dec_r16(uint16_t &reg);
  bool op_add_hl_r16(uint16_t &reg);

  bool op_inc_r8(uint8_t &reg);
  bool op_dec_r8(uint8_t &reg);

  bool op_ld_r8_imm8(uint8_t &reg);

  bool op_rlca();
  bool op_rrca();
  bool op_rla();
  bool op_rra();
  bool op_daa();
  bool op_cpl();
  bool op_scf();
  bool op_ccf();

  bool op_jr_imm8();
  bool op_jr_cond_imm8();

  bool op_stop();

  bool op_ld_r8_r8();

  bool op_halt();

  bool op_add_a_r8();
  bool op_adc_a_r8();
  bool op_sub_a_r8();
  bool op_sbc_a_r8();
  bool op_and_a_r8();
  bool op_xor_a_r8();
  bool op_or_a_r8();
  bool op_cp_a_r8();

  bool op_add_a_imm8();
  bool op_adc_a_imm8();
  bool op_sub_a_imm8();
  bool op_sbc_a_imm8();
  bool op_and_a_imm8();
  bool op_xor_a_imm8();
  bool op_or_a_imm8();
  bool op_cp_a_imm8();

  bool op_ret_cond();
  bool op_ret();
  bool op_reti();
  bool op_jp_cond_imm16();
  bool op_jp_imm16();
  bool op_jp_hl();
  bool op_call_cond_imm16();
  bool op_call_imm16();
  bool op_rst_tgt3();

  bool op_pop_r16stk();
  bool op_push_r16stk();

  bool op_ldh_c_a();
  bool op_ldh_imm8_a();
  bool op_ld_imm16_a();
  bool op_ldh_a_c();
  bool op_ldh_a_imm8();
  bool op_ld_a_imm16();

  bool op_add_sp_imm8();
  bool op_ld_hl_sp_imm8();
  bool op_ld_sp_hl();

  bool op_di();
  bool op_ei();
};
