use crate::core::emulator::Emulator;
use eframe::egui;
use std::sync::Arc;

pub struct GBCApp {
    emulator: Arc<Emulator>,
}

impl Default for GBCApp {
    fn default() -> Self {
        let emulator = Arc::new(Emulator::new());
        emulator.dispatch();
        Self { emulator }
    }
}

impl eframe::App for GBCApp {
    fn update(&mut self, ctx: &egui::Context, _: &mut eframe::Frame) {
        egui::TopBottomPanel::top("menu").show(ctx, |ui| {
            ui.columns(2, |columns| {
                let paused = self.emulator.is_paused();
                if columns[0]
                    .button(if paused { "Resume" } else { "Pause" })
                    .clicked()
                {
                    self.emulator.toggle_pause();
                }
                let step_mode = self.emulator.is_step_mode();
                if columns[1]
                    .button(if step_mode {
                        "Disable Step Mode"
                    } else {
                        "Enable Step Mode"
                    })
                    .clicked()
                {
                    self.emulator.toggle_step_mode();
                }
            });
        });

        egui::CentralPanel::default().show(ctx, |ui| {
            let mut img = egui::ColorImage::default();
            if let Ok(ppu) = self.emulator.ppu.lock() {
                // TODO: make faster
                img = egui::ColorImage::from_rgba_unmultiplied([160, 144], &ppu.to_rgba_flat());
            }

            let tex = ui
                .ctx()
                .load_texture("screen", img, egui::TextureOptions::NEAREST);
            ui.add(egui::Image::new(&tex).shrink_to_fit());
        });

        ctx.request_repaint_after(std::time::Duration::from_millis(16));
    }
}
