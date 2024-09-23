use std::{fs, time::Instant};

fn main() {
    let mut values = Vec::new();
    let path = "../../in.txt";
    for x in fs::read_to_string(path)
        .expect("Can not open the file")
        .split(',')
    {
        values.push(x.parse::<i32>().unwrap());
    }
    let now=Instant::now();
    let ans = Solution::max_score_sightseeing_pair(values);
    let elapsed_time=now.elapsed();
    println!("ans: {}, time: {} ns", ans,elapsed_time.as_nanos());
}

struct Solution {}

impl Solution {
    pub fn max_score_sightseeing_pair(values: Vec<i32>) -> i32 {
        let mut ans = 0i32;
        let mut mx=values[0];
        for j in 1..values.len(){
            ans=ans.max(mx+values[j]-j as i32);
            mx=mx.max(values[j]+j as i32);
        }
        ans
    }
}
