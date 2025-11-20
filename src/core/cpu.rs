use crate::core::types::{Flag, Reg8Bit, Reg16Bit};

#[derive(Debug)]
pub struct Cpu {
    a: Reg8Bit,
    b: Reg8Bit,
    c: Reg8Bit,
    d: Reg8Bit,
    e: Reg8Bit,
    h: Reg8Bit,
    l: Reg8Bit,

    af: Reg16Bit,
    bc: Reg16Bit,
    de: Reg16Bit,
    hl: Reg16Bit,

    sp: Reg16Bit,
    pc: Reg16Bit,

    z_flag: Flag,
    n_flag: Flag,
    h_flag: Flag,
    c_flag: Flag,
}

impl Cpu {
    pub fn new() -> Self {
        let a = Reg8Bit::new("a", 0);
        let b = Reg8Bit::new("b", 0);
        let c = Reg8Bit::new("c", 0);
        let d = Reg8Bit::new("d", 0);
        let e = Reg8Bit::new("e", 0);
        let f: Reg8Bit = Reg8Bit::new("f", 0);
        let h = Reg8Bit::new("h", 0);
        let l = Reg8Bit::new("l", 0);

        Self {
            a: a.clone(),
            b: b.clone(),
            c: c.clone(),
            d: d.clone(),
            e: e.clone(),
            h: h.clone(),
            l: l.clone(),

            af: Reg16Bit::new_with_regs("af", a, f.clone()),
            bc: Reg16Bit::new_with_regs("bc", b, c),
            de: Reg16Bit::new_with_regs("de", d, e),
            hl: Reg16Bit::new_with_regs("hl", h, l),

            sp: Reg16Bit::new("sp", 0),
            pc: Reg16Bit::new("pc", 0),

            z_flag: Flag::new("z_flag", f.clone(), 7),
            n_flag: Flag::new("n_flag", f.clone(), 6),
            h_flag: Flag::new("h_flag", f.clone(), 5),
            c_flag: Flag::new("c_flag", f, 4),
        }
    }

    pub fn tick(&self) {}
}
