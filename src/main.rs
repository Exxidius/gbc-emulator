mod emulator;

fn main() -> Result<(), eframe::Error> {
    let _emulator = emulator::Emulator::new()?;
    Ok(())
}
