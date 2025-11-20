use std::error::Error;
use std::sync::atomic::{AtomicU8, AtomicU16, Ordering};
use std::sync::{Arc, Mutex};

#[derive(Debug)]
pub struct Reg8Bit {
    reg: AtomicU8,
}

impl Reg8Bit {
    pub fn new(val: u8) -> Self {
        Self {
            reg: AtomicU8::new(val),
        }
    }
    pub fn store(&self, value: u8) {
        self.reg.store(value, Ordering::Relaxed);
    }

    pub fn load(&self) -> u8 {
        self.reg.load(Ordering::Relaxed)
    }
}

#[derive(Debug)]
pub struct UnifiedReg16Bit {
    reg: Arc<Mutex<u16>>,
}

// TODO: error handling
impl UnifiedReg16Bit {
    pub fn new(val: u16) -> Self {
        Self {
            reg: Arc::new(Mutex::new(val)),
        }
    }

    pub fn store(&self, val: u16) {
        if let Ok(mut reg) = self.reg.lock() {
            *reg = val;
        }
    }

    pub fn load(&self) -> u16 {
        if let Ok(reg) = self.reg.lock() {
            *reg
        } else {
            0
        }
    }
}

trait SetBytes {
    fn store_low(&self, value: u8);
    fn store_high(&self, value: u8);
    fn load_low(&self) -> u8;
    fn load_high(&self) -> u8;
}

impl SetBytes for UnifiedReg16Bit {
    fn store_low(&self, value: u8) {
        if let Ok(mut reg) = self.reg.lock() {
            *reg &= !0xff;
            *reg |= value as u16;
        }
    }

    fn store_high(&self, value: u8) {
        if let Ok(mut reg) = self.reg.lock() {
            *reg &= !0xff00;
            *reg |= (value as u16) << 8;
        }
    }

    fn load_low(&self) -> u8 {
        if let Ok(reg) = self.reg.lock() {
            (*reg & 0xff) as u8
        } else {
            0
        }
    }

    fn load_high(&self) -> u8 {
        if let Ok(reg) = self.reg.lock() {
            ((*reg & 0xff00) >> 8) as u8
        } else {
            0
        }
    }
}

#[derive(Debug)]
pub struct Reg16Bit {
    reg: AtomicU16,
}

impl Reg16Bit {
    pub fn new(val: u16) -> Self {
        Self {
            reg: AtomicU16::new(val),
        }
    }

    pub fn store(&self, value: u16) {
        self.reg.store(value, Ordering::Relaxed);
    }

    pub fn load(&self) -> u16 {
        self.reg.load(Ordering::Relaxed)
    }
}
