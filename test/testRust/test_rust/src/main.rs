use rand::Rng;
use std::time::Instant;

fn simple(input: &[u8]) -> Option<usize> {
    let mut idx = 0;
    while let Some(slice) = input.get(idx..idx + 14) {
        let mut state = 0u32;
        if let Some(pos) = slice.iter().rposition(|byte| {
            let bit_idx = byte % 32;
            let ret = state & (1 << bit_idx) != 0;
            state |= 1 << bit_idx;
            ret
        }) {
            idx += pos + 1;
        } else {
            return Some(idx);
        }
    }
    None
}

fn get_random_string(length: usize) -> String {
    rand::thread_rng()
        .sample_iter(rand::distributions::Alphanumeric)
        .take(length)
        .filter(|ch| ch.is_ascii_lowercase())
        .map(char::from)
        .collect()
}

fn main() {
    let start = Instant::now();
    let input = get_random_string(100000000);
    let result_pos = simple(input.as_bytes()).unwrap_or(input.len());
    let result = &input[result_pos..result_pos + 14];
    println!(
        "answer string: {}, time cost: {}ms",
        result,
        start.elapsed().as_millis()
    );
}
