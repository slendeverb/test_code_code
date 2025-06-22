fn main() -> Result<(), Box<dyn std::error::Error>> {
    // 配置文件和事件列表
    let file_path = "C:/Users/slendeverb/Downloads/MAA-v4.24.0-win-x64/debug/gui.log";
    let first_floor_event_list = vec![
        "解惑", "高空坠物", "在故事结束之后", "虫卡兹！", "相遇", "似是而非", "阴魂不散",
    ];

    // 读取并处理日志文件
    let in_file = File::open(file_path)?;
    let reader = BufReader::new(in_file);
    
    let mut event_appear_times: BTreeMap<String, u32> = BTreeMap::new();
    let event_regex = "事件: ";

    for line in reader.lines() {
        let line = line?;
        if let Some(start_pos) = line.find(event_regex) {
            let start_pos = start_pos + event_regex.len();
            let event_name = line[start_pos..].trim_end_matches(&['\r', '\n'][..]).to_string();
            
            if first_floor_event_list.contains(&&*event_name) {
                *event_appear_times.entry(event_name).or_insert(0) += 1;
            }
        }
    }

    // 准备数据
    let mut keys = Vec::new();
    let mut times = Vec::new();
    let mut probability = Vec::new();
    
    let total_times: u32 = event_appear_times.values().sum();
    for (key, &value) in &event_appear_times {
        keys.push(key.clone());
        times.push(value);
        probability.push((value as f64 / total_times as f64) * 100.0);
    }

    // 使用 plotters 绘图
    let picture_name="萨卡兹肉鸽一层不期而遇概率.png";
    let font_name="Microsoft YaHei";
    let root = BitMapBackend::new(picture_name, (800, 600)).into_drawing_area();
    root.fill(&WHITE)?;

    let max_times = *times.iter().max().unwrap_or(&1) as u32;
    let mut chart = ChartBuilder::on(&root)
        .caption(
            &picture_name[..picture_name.find('.').unwrap_or(picture_name.len())],
            (font_name, 30).into_font(),
        )
        .margin(10)
        .x_label_area_size(60)
        .y_label_area_size(80)
        .build_cartesian_2d(
            (0..keys.len()-1).into_segmented(),
            0.0..(max_times as f64+42.0),
        )?;

    chart
        .configure_mesh()
        .x_desc("不期而遇")
        .y_desc("出现次数")
        .axis_desc_style((font_name, 20))
        .label_style((font_name, 15))
        .x_label_formatter(&|x| match x {
            SegmentValue::CenterOf(i) | SegmentValue::Exact(i) => {
                if *i < keys.len() {
                    keys[*i].clone()
                } else {
                    "".to_string()
                }
            }
            _ => "".to_string(),
        })
        .draw()?;

    // 绘制柱状图
    chart.draw_series(
        Histogram::vertical(&chart)
            .style(RGBColor(255,165,0).filled())
            .margin(10)
            .data(keys.iter().enumerate().map(|(x, _)| (x, times[x] as f64))),
    )?;

    // 添加概率标签
    for (i, prob) in probability.iter().enumerate() {
        let x_coord = SegmentValue::CenterOf(i);
        let y_coord = times[i] as f64 + 10.0;

        let text_style = TextStyle::from((font_name, 15).into_font())
            .pos(Pos::new(HPos::Center, VPos::Bottom));
        
        chart.draw_series(std::iter::once(
            Text::new(
                format!("{:.1}%", prob),
                (x_coord, y_coord),
                text_style,
            )
        ))?;
    }

    root.present()?;
    println!("图像已保存为 {}",picture_name);

    Ok(())
}

#[allow(unused_imports)]
use std::cell::RefCell;
#[allow(unused_imports)]
use std::collections::{BTreeMap, HashMap};
#[allow(unused_imports)]
use std::fs::File;
#[allow(unused_imports)]
use std::io::{BufRead, BufReader};
#[allow(unused_imports)]
use std::rc::Rc;
#[allow(unused_imports)]
use std::str::FromStr;
#[allow(unused_imports)]
use std::usize;

#[allow(unused_imports)]
use plotters::prelude::*;
#[allow(unused_imports)]
use plotters::style::text_anchor::{HPos, Pos, VPos};

#[allow(dead_code)]
struct Solution {}

#[allow(dead_code)]
fn convert_two_dim<T, const M: usize, const N: usize>(arr: [[T; M]; N]) -> Vec<Vec<T>> {
    arr.into_iter()
        .map(|inner| inner.into_iter().collect())
        .collect()
}

#[allow(dead_code)]
fn convert_three_dim<T, const M: usize, const N: usize, const P: usize>(
    arr: [[[T; M]; N]; P],
) -> Vec<Vec<Vec<T>>> {
    arr.into_iter()
        .map(|mid| {
            mid.into_iter()
                .map(|inner| inner.into_iter().collect())
                .collect()
        })
        .collect()
}

#[allow(dead_code)]
fn convert_four_dim<T, const M: usize, const N: usize, const P: usize, const Q: usize>(
    arr: [[[[T; M]; N]; P]; Q],
) -> Vec<Vec<Vec<Vec<T>>>> {
    arr.into_iter()
        .map(|outer| {
            outer
                .into_iter()
                .map(|mid| {
                    mid.into_iter()
                        .map(|inner| inner.into_iter().collect())
                        .collect()
                })
                .collect()
        })
        .collect()
}

#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode<T = i64> {
    pub val: T,
    pub left: Option<Rc<RefCell<TreeNode<T>>>>,
    pub right: Option<Rc<RefCell<TreeNode<T>>>>,
}

impl<T> TreeNode<T> {
    #[inline]
    pub fn new(val: T) -> Self {
        TreeNode {
            val,
            left: None,
            right: None,
        }
    }
}

#[allow(dead_code)]
fn parse_tree_str<T>(s: &str) -> Vec<Option<T>>
where
    T: FromStr,
{
    let s = s.trim().trim_start_matches('[').trim_end_matches(']');

    s.split(',')
        .map(|part| {
            let part = part.trim();
            if part == "null" || part == "" {
                None
            } else {
                part.parse().ok()
            }
        })
        .collect()
}

type Tree<T> = Option<Rc<RefCell<TreeNode<T>>>>;
#[allow(dead_code)]
fn build_tree<T>(nums: &[Option<T>]) -> Tree<T>
where
    T: Clone + Default + std::fmt::Debug,
{
    if nums.is_empty() || nums[0].is_none() {
        return None;
    }

    let root = Rc::new(RefCell::new(TreeNode::new(
        nums[0].clone().unwrap_or_default(),
    )));
    let mut queue = std::collections::VecDeque::new();
    queue.push_back(Rc::clone(&root));
    let mut i = 1;

    while !queue.is_empty() && i < nums.len() {
        let node = queue.pop_front()?;
        let mut node = node.borrow_mut();

        if i < nums.len() {
            if let Some(val) = nums[i].clone() {
                let left = Rc::new(RefCell::new(TreeNode::new(val)));
                node.left = Some(Rc::clone(&left));
                queue.push_back(left);
            }
            i += 1;
        }

        if i < nums.len() {
            if let Some(val) = nums[i].clone() {
                let right = Rc::new(RefCell::new(TreeNode::new(val)));
                node.right = Some(Rc::clone(&right));
                queue.push_back(right);
            }
            i += 1;
        }
    }

    Some(root)
}
