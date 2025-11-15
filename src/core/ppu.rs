#[derive(Debug)]
pub struct Ppu {
    framebuffer: Vec<Color>,
}

#[derive(Debug, Clone)]
pub struct Color {
    pub r: u8,
    pub g: u8,
    pub b: u8,
    pub a: u8,
}

impl Ppu {
    pub fn new() -> Self {
        Self {
            framebuffer: vec![
                // #9bbc0f <-- Gameboy green
                Color {
                    r: 0x9b,
                    g: 0xbc,
                    b: 0x0f,
                    a: 0xff 
                };
                160 * 144
            ],
        }
    }

    pub fn set_pixel(&mut self, x: usize, y: usize, color: Color) {
        self.framebuffer[y * 160 + x] = color;
    }

    pub fn to_rgba_flat(&self) -> Vec<u8> {
        let mut rgba = Vec::with_capacity(self.framebuffer.len() * 4);
        for pixel in &self.framebuffer {
            rgba.push(pixel.r);
            rgba.push(pixel.g);
            rgba.push(pixel.b);
            rgba.push(pixel.a);
        }
        rgba
    }
}
