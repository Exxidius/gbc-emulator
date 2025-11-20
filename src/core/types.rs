use std::sync::{Arc, Mutex};

// TODO: Error handling for these data types! Not just wrapping in an Option

#[derive(Debug, Clone)]
pub struct Reg8Bit {
    name: &'static str,
    data: Arc<Mutex<u8>>,
}

impl Reg8Bit {
    pub fn new(name: &'static str, val: u8) -> Self {
        Self {
            name,
            data: Arc::new(Mutex::new(val)),
        }
    }

    pub fn store(&self, val: u8) {
        if let Ok(mut data) = self.data.lock() {
            *data = val;
        };
    }

    pub fn load(&self) -> Option<u8> {
        if let Ok(data) = self.data.lock() {
            Some(*data)
        } else {
            None
        }
    }
}

#[derive(Debug)]
pub struct Reg16Bit {
    name: &'static str,
    data_lower: Reg8Bit,
    data_higher: Reg8Bit,
}

impl Reg16Bit {
    pub fn new(name: &'static str, val: u16) -> Self {
        Self {
            name,
            data_lower: Reg8Bit::new("lower", (val & 0xff) as u8),
            data_higher: Reg8Bit::new("higher", ((val & 0xff00) >> 8) as u8),
        }
    }

    pub fn new_with_regs(name: &'static str, reg_high: Reg8Bit, reg_low: Reg8Bit) -> Self {
        Self {
            name,
            data_lower: reg_low,
            data_higher: reg_high,
        }
    }

    pub fn store(&self, val: u16) {
        self.store_higher(((val & 0xff00) >> 8) as u8);
        self.store_lower((val & 0xff) as u8);
    }
    pub fn load(&self) -> Option<u16> {
        if let Some(higher) = self.load_higher() {
            if let Some(lower) = self.load_lower() {
                return Some(((higher as u16) << 8) | lower as u16);
            }
        }
        None
    }

    pub fn store_lower(&self, val: u8) {
        self.data_lower.store(val);
    }
    pub fn load_lower(&self) -> Option<u8> {
        self.data_lower.load()
    }
    pub fn clone_lower(&self) -> Reg8Bit {
        self.data_lower.clone()
    }

    pub fn store_higher(&self, val: u8) {
        self.data_higher.store(val);
    }
    pub fn load_higher(&self) -> Option<u8> {
        self.data_higher.load()
    }
    pub fn clone_higher(&self) -> Reg8Bit {
        self.data_higher.clone()
    }
}

#[derive(Debug, Clone)]
pub struct Flag {
    name: &'static str,
    reg: Reg8Bit,
    offset: u8,
}

impl Flag {
    pub fn new(name: &'static str, reg: Reg8Bit, offset: u8) -> Self {
        Self { name, reg, offset }
    }

    pub fn set(&self, val: bool) {
        if let Ok(mut data) = self.reg.data.lock() {
            if val {
                *data |= 1 << self.offset;
            } else {
                *data &= !(1 << self.offset);
            }
        }
    }

    pub fn get(&self) -> Option<bool> {
        if let Ok(data) = self.reg.data.lock() {
            return Some(((*data >> self.offset) & 1) != 0);
        }
        None
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_reg8bit_store_and_load() {
        let reg = Reg8Bit::new("test", 0);
        reg.store(42);
        assert_eq!(reg.load(), Some(42));
    }

    #[test]
    fn test_reg8bit_clone_shares_data() {
        let reg1 = Reg8Bit::new("test", 0);
        let reg2 = reg1.clone();

        reg1.store(100);
        assert_eq!(reg2.load(), Some(100));

        reg2.store(200);
        assert_eq!(reg1.load(), Some(200));
    }

    #[test]
    fn test_reg16bit_store_and_load() {
        let reg = Reg16Bit::new("test", 0);
        reg.store(0x1234);
        assert_eq!(reg.load(), Some(0x1234));
    }

    #[test]
    fn test_reg16bit_high_low_bytes() {
        let reg = Reg16Bit::new("test", 0xABCD);
        assert_eq!(reg.load_higher(), Some(0xAB));
        assert_eq!(reg.load_lower(), Some(0xCD));
    }

    #[test]
    fn test_reg16bit_store_high_low_separately() {
        let reg = Reg16Bit::new("test", 0);
        reg.store_higher(0x12);
        reg.store_lower(0x34);
        assert_eq!(reg.load(), Some(0x1234));
    }

    #[test]
    fn test_reg16bit_with_shared_regs() {
        let high = Reg8Bit::new("high", 0x12);
        let low = Reg8Bit::new("low", 0x34);

        let reg16 = Reg16Bit::new_with_regs("test", high.clone(), low.clone());

        assert_eq!(reg16.load(), Some(0x1234));

        high.store(0xAB);
        assert_eq!(reg16.load(), Some(0xAB34));
        assert_eq!(reg16.load_higher(), Some(0xAB));

        low.store(0xCD);
        assert_eq!(reg16.load(), Some(0xABCD));
        assert_eq!(reg16.load_lower(), Some(0xCD));
    }

    #[test]
    fn test_reg16bit_modifying_via_16bit_affects_8bit_regs() {
        let high = Reg8Bit::new("high", 0);
        let low = Reg8Bit::new("low", 0);

        let reg16 = Reg16Bit::new_with_regs("test", high.clone(), low.clone());

        reg16.store(0x5678);

        assert_eq!(high.load(), Some(0x56));
        assert_eq!(low.load(), Some(0x78));
    }

    #[test]
    fn test_reg16bit_store_higher_affects_shared_reg() {
        let high = Reg8Bit::new("high", 0);
        let low = Reg8Bit::new("low", 0);

        let reg16 = Reg16Bit::new_with_regs("test", high.clone(), low.clone());

        reg16.store_higher(0xFF);
        assert_eq!(high.load(), Some(0xFF));
        assert_eq!(reg16.load(), Some(0xFF00));
    }

    #[test]
    fn test_reg16bit_store_lower_affects_shared_reg() {
        let high = Reg8Bit::new("high", 0);
        let low = Reg8Bit::new("low", 0);

        let reg16 = Reg16Bit::new_with_regs("test", high.clone(), low.clone());

        reg16.store_lower(0xEE);
        assert_eq!(low.load(), Some(0xEE));
        assert_eq!(reg16.load(), Some(0x00EE));
    }

    #[test]
    fn test_flag_set_and_get() {
        let reg = Reg8Bit::new("flags", 0);
        let flag = Flag::new("zero", reg.clone(), 7);

        assert_eq!(flag.get(), Some(false));

        flag.set(true);
        assert_eq!(flag.get(), Some(true));
        assert_eq!(reg.load(), Some(0b10000000));

        flag.set(false);
        assert_eq!(flag.get(), Some(false));
        assert_eq!(reg.load(), Some(0b00000000));
    }

    #[test]
    fn test_flag_clear_doesnt_affect_other_bits() {
        let reg = Reg8Bit::new("flags", 0b11111111);
        let flag3 = Flag::new("bit3", reg.clone(), 3);

        assert_eq!(flag3.get(), Some(true));

        flag3.set(false);
        assert_eq!(flag3.get(), Some(false));
        assert_eq!(reg.load(), Some(0b11110111));
    }

    #[test]
    fn test_flag_toggle_multiple_times() {
        let reg = Reg8Bit::new("test", 0);
        let flag = Flag::new("bit2", reg.clone(), 2);

        for i in 0..10 {
            let expected = i % 2 == 1;
            flag.set(expected);
            assert_eq!(flag.get(), Some(expected));
        }
    }

    #[test]
    fn test_multiple_flags_on_same_register() {
        let reg = Reg8Bit::new("flags", 0);
        let flag0 = Flag::new("bit0", reg.clone(), 0);
        let flag7 = Flag::new("bit7", reg.clone(), 7);

        flag0.set(true);
        assert_eq!(flag0.get(), Some(true));
        assert_eq!(reg.load(), Some(0b00000001));

        flag7.set(true);
        assert_eq!(flag7.get(), Some(true));
        assert_eq!(reg.load(), Some(0b10000001));

        assert_eq!(flag0.get(), Some(true));
        assert_eq!(flag7.get(), Some(true));
    }

    #[test]
    fn test_clone_higher_and_lower_share_data() {
        let reg16 = Reg16Bit::new("test", 0x1234);

        let high_clone = reg16.clone_higher();
        let low_clone = reg16.clone_lower();

        assert_eq!(high_clone.load(), Some(0x12));
        assert_eq!(low_clone.load(), Some(0x34));

        reg16.store(0xABCD);
        assert_eq!(high_clone.load(), Some(0xAB));
        assert_eq!(low_clone.load(), Some(0xCD));

        high_clone.store(0x99);
        low_clone.store(0x88);
        assert_eq!(reg16.load(), Some(0x9988));
    }
}
