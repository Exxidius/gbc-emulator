use crate::core::{cartridge, cpu, ppu, timer};
use std::sync::atomic::{AtomicBool, Ordering};
use std::sync::{Arc, Mutex};
use std::thread;

#[derive(Debug, Clone)]
pub struct Emulator {
    pub cpu: Arc<cpu::Cpu>,
    pub cartridge: Arc<Mutex<cartridge::Cartridge>>,
    pub ppu: Arc<Mutex<ppu::Ppu>>,
    pub timer: Arc<timer::Timer>,
    pub state: Arc<EmulatorState>,
}

#[derive(Debug, Default)]
pub struct EmulatorState {
    paused: AtomicBool,
    step_mode: AtomicBool,
}

impl Emulator {
    pub fn new() -> Self {
        let ppu = Arc::new(Mutex::new(ppu::Ppu::new()));
        let cpu = Arc::new(cpu::Cpu::new());
        let cartridge = Arc::new(Mutex::new(cartridge::Cartridge::new()));
        let timer = Arc::new(timer::Timer::new());
        let state = Arc::new(EmulatorState::default());

        let emulator = Self {
            cpu: cpu.clone(),
            cartridge: cartridge.clone(),
            ppu: ppu.clone(),
            timer: timer.clone(),
            state: state.clone(),
        };

        emulator
    }

    pub fn dispatch(&self) {
        let emu_clone = self.clone();
        thread::spawn(move || {
            loop {
                if !emu_clone.is_paused() {
                    emu_clone.tick();
                }
                thread::sleep(std::time::Duration::from_millis(1));
            }
        });
    }

    pub fn tick(&self) {
        self.cpu.tick();
        self.timer.tick();
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
