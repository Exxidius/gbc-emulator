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
    std::function<void()> handler;
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

  uint8_t readByte(uint16_t addr);

  void initOpCodeTable();

  void op_nop();

  void op_ld_r16_imm16(uint16_t &reg);
  void op_ld_r16mem_a();
  void op_ld_a_r16mem();
  void op_ld_imm16mem_sp();

  void op_inc_r16();
  void op_dec_r16();
  void op_add_hl_r16();

  void op_inc_r8();
  void op_dec_r8();

  void op_ld_r8_imm8();

  void op_rlca();
  void op_rrca();
  void op_rla();
  void op_rra();
  void op_daa();
  void op_cpl();
  void op_scf();
  void op_ccf();

  void op_jr_imm8();
  void op_jr_cond_imm8();

  void op_stop();

  void op_ld_r8_r8();

  void op_halt();

  void op_add_a_r8();
  void op_adc_a_r8();
  void op_sub_a_r8();
  void op_sbc_a_r8();
  void op_and_a_r8();
  void op_xor_a_r8();
  void op_or_a_r8();
  void op_cp_a_r8();

  void op_add_a_imm8();
  void op_adc_a_imm8();
  void op_sub_a_imm8();
  void op_sbc_a_imm8();
  void op_and_a_imm8();
  void op_xor_a_imm8();
  void op_or_a_imm8();
  void op_cp_a_imm8();

  void op_ret_cond();
  void op_ret();
  void op_reti();
  void op_jp_cond_imm16();
  void op_jp_imm16();
  void op_jp_hl();
  void op_call_cond_imm16();
  void op_call_imm16();
  void op_rst_tgt3();

  void op_pop_r16stk();
  void op_push_r16stk();

  void op_ldh_c_a();
  void op_ldh_imm8_a();
  void op_ld_imm16_a();
  void op_ldh_a_c();
  void op_ldh_a_imm8();
  void op_ld_a_imm16();

  void op_add_sp_imm8();
  void op_ld_hl_sp_imm8();
  void op_ld_sp_hl();

  void op_di();
  void op_ei();
};
