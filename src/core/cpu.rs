#[derive(Debug, Clone)]
pub struct Cpu {
    test: u8,
}

impl Cpu {
    pub fn new() -> Self {
        Self { test: 0 }
    }

    pub fn tick(&mut self) {
        self.test = 1;
    }
}
