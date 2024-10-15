use std::time::Instant;

impl Solution {
    pub fn max_height_of_triangle(red: i32, blue: i32) -> i32 {
        fn max_height(x: i32, y: i32) -> i32 {
            let odd = 2 * ((x as f64).sqrt() as i32) - 1;
            let even = 2 * (((-1.0 + (1.0 + 4.0 * y as f64).sqrt()) / 2.0) as i32);
            std::cmp::min(odd, even) + 1
        }
        std::cmp::max(max_height(red, blue), max_height(blue, red))
    }
}

struct Solution {}

fn main() {
    let now = Instant::now();
    let red = 10;
    let blue = 20;
    println!("{}",Solution::max_height_of_triangle(red,blue));
    println!("{}",now.elapsed().as_micros());
}
