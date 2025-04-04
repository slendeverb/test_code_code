impl Solution {
    pub fn most_points(questions:Vec<Vec<i32>>)->i64{
        let n=questions.len();
        let mut f=vec![0i64;n+1];
        for i in 0..f.len()-1{
            f[i]=questions[i][0] as i64;
        }
        for i in (0..=n-1).rev() {
            let skip_idx=if i+1>=n {n} else {i+1};
            let choose_idx=if i+questions[i][1] as usize+1>=n {n} else {i+questions[i][1] as usize+1};
            f[i]=f[i].max(f[skip_idx]).max(f[choose_idx]+questions[i][0] as i64);
        }
        f[0]
    }
}

struct Solution {}

fn main() {
    let mut questions=vec![vec![0;2];100000];
    for i in 0..questions.len(){
        questions[i][0]=i as i32;
        questions[i][1]=i as i32;
    }
    let result=Solution::most_points(questions);
    print!("{:?}\n",result);
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
