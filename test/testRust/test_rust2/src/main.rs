use std::{env, process};

use test_rust2::{self, Config};

fn main() {
    let config = Config::new(env::args()).unwrap_or_else(|err| {
        eprintln!("Problem parsing arguments: {}", err);
        process::exit(1);
    });
    match test_rust2::run(config) {
        Ok(_) => {}
        Err(e) => {
            eprintln!("Application error: {}", e);
            process::exit(1);
        }
    }
}
