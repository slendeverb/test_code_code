use std::collections::HashSet;

impl Solution {
    pub fn distinct_names(ideas: Vec<String>) -> i64 {
        let mut groups=vec![HashSet::new();26];
        for s in ideas.iter(){
            groups[(s.as_bytes()[0]-b'a')as usize].insert(&s[1..]);
        }
        let mut res=0i64;
        for i in 1..26{
            for j in 0..i{
                let m=groups[i].iter().filter(|&s| groups[j].contains(s)).count();
                res+=(groups[i].len()-m) as i64*(groups[j].len()-m) as i64;
            }
        }
        res*2
    }
}

struct Solution {}

fn main() {
    let ideas = vec![
        "coffee".to_string(),
        "donuts".to_string(),
        "time".to_string(),
        "toffee".to_string(),
    ];
    println!("{}", Solution::distinct_names(ideas));
}
