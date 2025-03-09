impl Solution {
    pub fn maximum_beauty(mut items: Vec<Vec<i32>>, queries: Vec<i32>) -> Vec<i32> {
        items.sort_unstable_by_key(|item| item[0]);
        items.dedup_by(|b,a| b[1]<=a[1]);

        queries.into_iter().map(|q| {
            let j = items.partition_point(|item| item[0] <= q);
            if j > 0 {
                items[j - 1][1]
            } else {
                0
            }
        }).collect()
    }
}

struct Solution {}

fn main() {
    let items = vec![vec![1, 2], vec![3, 2], vec![2, 4], vec![5, 6], vec![3, 5]];
    let queries = vec![1, 2, 3, 4, 5, 6];
    println!("{:?}", Solution::maximum_beauty(items, queries));
}
