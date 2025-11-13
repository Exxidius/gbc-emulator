use eframe::egui;

mod emulator;

fn main() -> eframe::Result {
    let options = eframe::NativeOptions {
        viewport: egui::ViewportBuilder::default()
            .with_inner_size([337.0, 387.0])
            .with_resizable(false),
        ..Default::default()
    };

    eframe::run_native(
        "Game Boy Color Emulator",
        options,
        Box::new(|_cc| Ok(Box::<emulator::Emulator>::default())),
    )
}

impl eframe::App for emulator::Emulator {
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        egui::CentralPanel::default().show(ctx, |ui| {
            ui.horizontal(|ui| {
                let name_label = ui.label("Your name: ");
                ui.text_edit_singleline(&mut self.name)
                    .labelled_by(name_label.id);
            });
            ui.add(egui::Slider::new(&mut self.age, 0..=120).text("age"));
            if ui.button("Increment").clicked() {
                self.age += 1;
            }
            ui.label(format!("Hello '{}', age {}", self.name, self.age));

            let (rect, _response) =
                ui.allocate_exact_size(egui::vec2(320.0, 288.0), egui::Sense::hover());

            let painter = ui.painter();

            let scale = 2.0;
            for y in 0..emulator::SCREEN_HEIGHT {
                for x in 0..emulator::SCREEN_WIDTH {
                    let (r, g, b, _a) = self.get_pixel_color(x, y);
                    let color = egui::Color32::from_rgb(r, g, b);

                    let pos =
                        egui::pos2(rect.min.x + x as f32 * scale, rect.min.y + y as f32 * scale);
                    painter.rect_filled(
                        egui::Rect::from_min_size(pos, egui::vec2(scale, scale)),
                        0.0,
                        color,
                    );
                }
            }
            // use for repaint e.g. draw call for gbc
            ctx.request_repaint();
        });
    }
}
