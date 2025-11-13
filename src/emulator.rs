pub const SCREEN_WIDTH: usize = 160;
pub const SCREEN_HEIGHT: usize = 144;

#[derive(Debug)]
pub struct Emulator {
    pub name: String,
    pub age: u32,
    pub screen_buffer: Vec<u8>,
}

impl Default for Emulator {
    fn default() -> Self {
        Self {
            name: String::new(),
            age: 0,
            screen_buffer: vec![155, 188, 15, 255].repeat(SCREEN_WIDTH * SCREEN_HEIGHT),
        }
    }
}

impl Emulator {
    pub fn get_pixel_color(&self, x: usize, y: usize) -> (u8, u8, u8, u8) {
        if x < SCREEN_WIDTH && y < SCREEN_HEIGHT {
            let idx = (y * SCREEN_WIDTH + x) * 4;
            (
                self.screen_buffer[idx],
                self.screen_buffer[idx + 1],
                self.screen_buffer[idx + 2],
                self.screen_buffer[idx + 3],
            )
        } else {
            (0, 0, 0, 255)
        }
    }
}
