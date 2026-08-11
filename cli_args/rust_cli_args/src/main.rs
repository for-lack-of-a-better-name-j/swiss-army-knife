use clap::Parser;
use std::{error::Error, path::PathBuf};

#[derive(Parser, Debug)]
#[command(version, about = "CLI argument parser demonstration", long_about = None)]
struct Cli {
    /// Enable verbose output
    #[arg(short, long)]
    verbose: bool,
    /// Count of tasks to execute [default = 1]
    #[arg(short, long, default_value_t = 1)]
    count: usize,
    /// path to run tasks on
    target: PathBuf,
}
fn main() -> Result<(), Box<dyn Error>> {
    let args = Cli::parse();
    println!("Target path: {}", args.target.display());
    if args.verbose {
        for idx in 0..args.count {
            println!("Verbose pass {idx} on target: {}", args.target.display());
        }
    }
    Ok(())
}
