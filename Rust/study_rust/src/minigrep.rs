use std::{env, fs, process};

#[allow(dead_code)]
pub fn run() {
    let mut args = env::args().skip(1);
    let may_ignore_case = if args.len() == 2 {
        |x| x
    } else if args.len() == 3 && args.next().unwrap() == "-i" {
        |x: String| x.to_lowercase()
    } else {
        eprintln!("Usage: minigrep [-i] <pattern> <file>");
        process::exit(0);
    };

    let (pattern, file) = (may_ignore_case(args.next().unwrap()), args.next().unwrap());
    let contents = fs::read_to_string(&file).unwrap_or_else(|err| {
        eprintln!("Error: Failed to read the file \"{file}\": {err}.");
        process::exit(0);
    });

    for s in contents
        .lines()
        .filter(|line| may_ignore_case(line.to_string()).contains(&pattern))
    {
        println!("{s}");
    }
}
