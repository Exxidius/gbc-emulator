use crate::core::ppu::Ppu;
use std::sync::atomic::{AtomicBool, Ordering};
use std::sync::{Arc, Mutex};
use std::thread;

#[derive(Debug, Clone)]
pub struct Emulator {
    pub ppu: Arc<Mutex<Ppu>>,
    pub state: Arc<EmulatorState>,
}

#[derive(Debug, Default)]
pub struct EmulatorState {
    paused: AtomicBool,
    step_mode: AtomicBool,
}

impl Emulator {
    pub fn new() -> Self {
        let ppu = Arc::new(Mutex::new(Ppu::new()));
        let state = Arc::new(EmulatorState::default());

        let emulator = Self {
            ppu: ppu.clone(),
            state: state.clone(),
        };

        emulator
    }

    pub fn dispatch(&self) {
        let emu_clone = self.clone();
        thread::spawn(move || {
            loop {
                if !emu_clone.is_paused() {
                    emu_clone.run();
                }
                thread::sleep(std::time::Duration::from_millis(1));
            }
        });
    }

    pub fn run(&self) {
        let x = rand::random_range(0..160);
        let y = rand::random_range(0..144);
        let color = crate::core::ppu::Color {
            r: rand::random_range(0..=255),
            g: rand::random_range(0..=255),
            b: rand::random_range(0..=255),
            a: 0xff,
        };

        if let Ok(mut ppu) = self.ppu.lock() {
            ppu.set_pixel(x, y, color);
        }
    }

    pub fn is_paused(&self) -> bool {
        self.state.paused.load(Ordering::Relaxed)
    }

    pub fn is_step_mode(&self) -> bool {
        self.state.step_mode.load(Ordering::Relaxed)
    }

    pub fn toggle_step_mode(&self) {
        self.state.step_mode.fetch_xor(true, Ordering::Relaxed);
    }

    pub fn toggle_pause(&self) {
        self.state.paused.fetch_xor(true, Ordering::Relaxed);
    }
}
