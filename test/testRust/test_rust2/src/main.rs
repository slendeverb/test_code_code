impl Solution{
    pub fn maximum_beauty(mut flowers:Vec<i32>,new_flowers:i64,target:i32,full:i32,partial:i32)->i64{
        let n=flowers.len() as i64;
        let full=full as i64;
        let partial=partial as i64;
        let target=target as i64;
        
        let mut left_flowers=new_flowers-target*n;
        for flower in &mut flowers{
            *flower=(*flower).min(target as i32);
            left_flowers+=*flower as i64;
        }
        
        if left_flowers==new_flowers{
            return n*full;
        }

        if left_flowers>=0{
            return ((target-1)*partial+(n-1)*full).max(n*full);
        }

        flowers.sort_unstable();

        let mut ans=0;
        let mut pre_sum=0;
        let mut j=0;

        for i in 1..=n as usize{
            left_flowers+=target-flowers[i-1] as i64;
            if left_flowers<0{
                continue;
            }

            while j<i && flowers[j] as i64*j as i64<=pre_sum+left_flowers{
                pre_sum+=flowers[j] as i64;
                j+=1;
            }

            let avg=(left_flowers+pre_sum)/j as i64;
            let total_beauty=avg*partial+(n-i as i64)*full;
            ans=ans.max(total_beauty);
        }
        ans
    }
}

struct Solution{
}

fn main() {
    let flowers=vec![2,4,5,3];
    let new_flowers=10;
    let target=5;
    let full=2;
    let partial=6;
    println!("total beauty:{}",Solution::maximum_beauty(flowers, new_flowers, target, full, partial));
}
