mod core;
mod ui;

use ui::app::GBCApp;

fn main() -> eframe::Result<()> {
    let options = eframe::NativeOptions {
        viewport: egui::ViewportBuilder::default()
            .with_inner_size([500.0, 700.0])
            .with_resizable(false),
        ..Default::default()
    };

    eframe::run_native(
        "Game Boy Color Emulator",
        options,
        Box::new(|_cc| Ok(Box::<GBCApp>::default())),
    )
}
