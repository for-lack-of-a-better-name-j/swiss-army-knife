use std::{env, error::Error, path::PathBuf};

use walkdir::WalkDir;

fn main() -> Result<(), Box<dyn Error>> {
    // Get the 1st argument (index 1), or default to "."
    let target_dir = env::args()
        .nth(1)
        .map(PathBuf::from)
        .unwrap_or_else(|| PathBuf::from("."));

    for entry in WalkDir::new(target_dir) {
        let entry = entry?;
        println!("{}", entry.path().display());
        // to check if it is a file: (do note that is_file() will return false
        // if the user does not have sufficient permissions)
        // println!("{}", entry.path().is_file());
    }

    Ok(())
}
