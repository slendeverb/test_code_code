
fn main() {
    let edges=vec![1,0,0,0,0,7,7,5];
    let so=Solution::edge_score(edges);
    println!("{so}");
}

struct Solution{
    
}

impl Solution{
    pub fn edge_score(edges:Vec<i32>)->i32{
        let n=edges.len();
        let mut score=vec![0i64;n];
        for (i,&edge) in edges.iter().enumerate() {
            score[edge as usize]+=i as i64;
        }
        let mut max=0i64;
        let mut ans=0i32;
        for (i,&val) in score.iter().enumerate(){
            if val>max{
                max=val;
                ans=i as i32;
            }
        }
        ans
    }
}