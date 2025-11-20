use crate::core::types::{Reg16Bit, UnifiedReg16Bit};

#[derive(Debug)]
pub struct Cpu {
    af: UnifiedReg16Bit,
    bc: UnifiedReg16Bit,
    de: UnifiedReg16Bit,
    hl: UnifiedReg16Bit,

    sp: Reg16Bit,
    pc: Reg16Bit,
}

impl Cpu {
    pub fn new() -> Self {
        Self {
            af: UnifiedReg16Bit::new(0),
            bc: UnifiedReg16Bit::new(0),
            de: UnifiedReg16Bit::new(0),
            hl: UnifiedReg16Bit::new(0),

            sp: Reg16Bit::new(0),
            pc: Reg16Bit::new(0),
        }
    }

    pub fn tick(&self) {}
}
