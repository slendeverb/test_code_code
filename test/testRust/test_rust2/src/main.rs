use std::io::stdin;

impl Solution {
    pub fn difference_of_distinct_values(grid: Vec<Vec<i32>>) -> Vec<Vec<i32>> {
        let m = grid.len();
        let n = grid[0].len();
        let mut ans = vec![vec![0; n]; m];
        let mut st;

        for k in 0..(m + n) {
            let min_j = 0.max(n as i32 - k as i32) as usize;
            let max_j = (m as i32 + n as i32 - 1 - k as i32).min(n as i32 - 1) as usize;

            st = 0u64;
            for j in min_j..=max_j {
                let i = k + j - n;
                ans[i][j] = st.count_ones() as i32;
                st |= 1u64 << grid[i][j];
            }

            st = 0u64;
            for j in (min_j..=max_j).rev() {
                let i = k + j - n;
                ans[i][j] = (ans[i][j] - st.count_ones() as i32).abs();
                st |= 1u64 << grid[i][j];
            }
        }
        ans
    }
}

struct Solution {}

fn main() {
    let grid = [
        [15, 42, 48, 22, 36, 47, 13, 23, 31, 41],
        [25, 3, 44, 17, 37, 9, 14, 37, 4, 43],
        [7, 15, 38, 10, 25, 7, 37, 6, 43, 4],
        [50, 9, 14, 36, 35, 36, 44, 17, 10, 44],
        [46, 50, 45, 28, 10, 18, 18, 3, 42, 24],
        [14, 11, 13, 32, 37, 31, 50, 32, 12, 38],
        [44, 24, 42, 9, 32, 40, 8, 20, 46, 39],
        [33, 5, 42, 30, 20, 37, 26, 38, 30, 30],
        [32, 39, 31, 33, 41, 23, 4, 29, 44, 22],
        [8, 8, 11, 21, 9, 2, 37, 19, 30, 37],
    ];
    let grid = convert_two_dim(grid);
    let result = Solution::difference_of_distinct_values(grid);
    print!("{:?}\n", result);
    assert_eq!(
        convert_two_dim([
            [8, 8, 7, 6, 5, 4, 3, 1, 1, 0],
            [8, 6, 6, 5, 4, 3, 2, 1, 0, 1],
            [6, 6, 5, 4, 3, 2, 1, 0, 1, 2],
            [6, 4, 4, 3, 2, 1, 0, 1, 2, 3],
            [5, 4, 2, 2, 1, 0, 1, 2, 3, 4],
            [4, 3, 3, 1, 0, 1, 2, 3, 4, 5],
            [3, 2, 1, 1, 1, 2, 3, 4, 5, 6],
            [2, 1, 0, 1, 1, 2, 4, 5, 6, 7],
            [1, 0, 1, 2, 3, 3, 4, 6, 6, 8],
            [0, 1, 2, 3, 4, 5, 5, 6, 8, 8]
        ]),
        result
    );

    let mut line=String::new();
    match stdin().read_line(&mut line) {
        Ok(_)=>{
            print!("You typed: {}\n",line.trim());
        }
        Err(error)=>{
            print!("Error reading input: {}\n",error);
        }
    }
}

#[allow(dead_code)]
fn convert_two_dim<T, const M: usize, const N: usize>(arr: [[T; M]; N]) -> Vec<Vec<T>> {
    let mut ret = Vec::with_capacity(N);
    for v in arr.into_iter() {
        ret.push(v.into_iter().collect());
    }
    ret
}

#[allow(dead_code)]
fn convert_three_dim<T, const M: usize, const N: usize, const P: usize>(
    arr: [[[T; M]; N]; P],
) -> Vec<Vec<Vec<T>>> {
    let mut ret = Vec::with_capacity(P);
    for v in arr.into_iter() {
        let mut tmp = Vec::with_capacity(N);
        for w in v.into_iter() {
            tmp.push(w.into_iter().collect());
        }
        ret.push(tmp);
    }
    ret
}

#[allow(dead_code)]
fn convert_four_dim<T, const M: usize, const N: usize, const P: usize, const Q: usize>(
    arr: [[[[T; M]; N]; P]; Q],
) -> Vec<Vec<Vec<Vec<T>>>> {
    let mut ret = Vec::with_capacity(Q);
    for v in arr.into_iter() {
        let mut tmp1 = Vec::with_capacity(P);
        for w in v.into_iter() {
            let mut tmp2 = Vec::with_capacity(N);
            for u in w.into_iter() {
                tmp2.push(u.into_iter().collect());
            }
            tmp1.push(tmp2);
        }
        ret.push(tmp1);
    }
    ret
}
