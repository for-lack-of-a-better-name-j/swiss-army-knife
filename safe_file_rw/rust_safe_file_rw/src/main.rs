use std::fs::OpenOptions;
use std::io::Write;
fn main() -> Result<(), Box<dyn std::error::Error>> {
    let mut file = OpenOptions::new()
        .append(true)
        .create(true)
        .open("output.txt")?;

    writeln!(file, "new log entry")?;
    Ok(())
}
