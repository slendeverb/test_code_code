impl Solution {
    pub fn weekday(year: u32, month: u32, day: u32) -> char {
        let mut offset = 0u32;

        // 累计前面年份的天数
        for y in 1..year {
            if Solution::is_leap_year(y) {
                offset += 366;
            } else {
                offset += 365;
            }
        }

        // 月份天数表
        let mut months = vec![0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];
        if Solution::is_leap_year(year) {
            months[2] = 29; // 闰年二月调整
        }

        // 累计当年的月份天数
        for m in 1..month {
            offset += months[m as usize];
        }

        // 累计当前月的天数
        offset += day;

        // 求出星期几
        let res = ['日', '一', '二', '三', '四', '五', '六'];
        res[(offset % 7) as usize]
    }

    // 判断是否为闰年
    fn is_leap_year(year: u32) -> bool {
        year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)
    }
}

struct Solution{
}

fn main() {
    let year=2024;
    let month=1;
    let day=1;
    let weekday=Solution::weekday(year, month, day);
    println!("{}年{}月{}日是星期{}",year,month,day,weekday);
}
