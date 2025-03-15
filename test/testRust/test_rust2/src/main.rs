impl Solution {
    pub fn is_balanced(num: String) -> bool {
        let num=num.as_bytes();
        let mut odd_sum=0;
        let mut even_sum=0;
        for (i,digit) in num.iter().enumerate(){
            if i%2==0{
                even_sum+=digit-'0' as u8;
            }else{
                odd_sum+=digit-'0' as u8;
            }
        }
        if odd_sum==even_sum{
            true
        }else{
            false
        }
    }
}

struct Solution {}

fn main() {
    let num=String::from("24123");
    println!("{:?}",Solution::is_balanced(num));
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
