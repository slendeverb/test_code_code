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
    return None;
}

fn main() {
    let input =
        String::from("abafawfgugflgfwlqgtqtgquofgcqoefbzbfftqjtgqoqwertyuiopasdfghjklzxcvbnm");
    let result_pos = simple(input.as_bytes()).unwrap_or(usize::MAX);
    let result = &input[result_pos..result_pos + 14];
    println!("{}", result);
}
