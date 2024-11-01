use std::time::Instant;

fn main() {
    let now = Instant::now();
    for i in 0..1_0000_0 {
        println!("{}", i);
    }
    println!("{}", now.elapsed().as_millis());
}
