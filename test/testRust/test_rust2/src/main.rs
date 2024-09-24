use std::fs;

struct Solution {
    text: String,
    pattern: String,
}

impl<'a> FromIterator<&'a str> for Solution {
    fn from_iter<T: IntoIterator<Item = &'a str>>(iter: T) -> Self {
        let mut into_iter = iter.into_iter();
        let text = into_iter.next().unwrap_or_default().to_string();
        let pattern = into_iter.into_iter().next().unwrap_or_default().to_string();
        Solution { text, pattern }
    }
}

impl Solution {
    pub fn maximum_subsequence_count(text: String, pattern: String) -> i64 {
        let pattern = pattern.as_bytes();
        let x = pattern[0];
        let y = pattern[1];
        let mut cnt0 = 0;
        let mut cnt1 = 0;
        let mut res = 0i64;
        for ch in text.bytes() {
            if ch == y {
                res += cnt0;
                cnt1 += 1;
            }
            if ch == x {
                cnt0 += 1;
            }
        }
        res + cnt0.max(cnt1)
    }
}

fn main() {
    let path = "../../in.txt";
    let content = fs::read_to_string(path)
        .expect("can not open file")
        .split_whitespace()
        .collect::<Solution>();
    let ans = Solution::maximum_subsequence_count(content.text, content.pattern);
    println!("{}", ans);
}
