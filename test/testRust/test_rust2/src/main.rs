fn main() -> Result<(), Box<dyn std::error::Error>> {
    let path="C:/Users/slendeverb/Downloads/MAA-v4.24.0-win-x64/debug/gui.log";
    let mut added_money: HashMap<i32, u32> = HashMap::new();
    let file = File::open(path)?;
    let reader = BufReader::new(file);
    for line in reader.lines() {
        let line = line?;
        if line.contains("已投资 ") && line.contains("(+") {
            let start=line.find("(+").unwrap_or(0);
            let substring = &line[start + 2..];
            let end=substring.find(")").unwrap_or(substring.len());
            let money_str = &substring[..end];
            let money=money_str.parse::<i32>()?;
            *added_money.entry(money).or_insert(0) += 1;
        }
    }
    
    let mut keys: Vec<i32> = added_money.keys().cloned().collect();
    keys.sort();
    let values: Vec<u32> = keys.iter().map(|k| added_money[k]).collect();

    let root = BitMapBackend::new("money_chart.png", (1024, 768)).into_drawing_area();
    root.fill(&WHITE)?;

    let max_count = *values.iter().max().unwrap_or(&1) as u32;
    let min_key = *keys.first().unwrap_or(&0);
    let max_key = *keys.last().unwrap_or(&0);

    let text_style="Microsoft YaHei";

    let mut chart = ChartBuilder::on(&root)
        .caption("投资金额统计", (text_style, 50))
        .margin(10)
        .x_label_area_size(60)
        .y_label_area_size(60)
        .build_cartesian_2d(
            min_key..max_key + 1,
            0u32..(max_count + 1),
        )?;

    chart
        .configure_mesh()
        .x_desc("金额")
        .y_desc("次数")
        .x_label_style((text_style,20))
        .y_label_style((text_style,20))
        .axis_desc_style((text_style, 25))
        .draw()?;

    chart.draw_series(
        Histogram::vertical(&chart)
            .style(RGBColor(255, 165, 0).filled())
            .margin(3)
            .data(keys.iter().zip(values.iter()).map(|(k, v)| (*k, *v))),
    )?;

    root.present()?;
    println!("图表已保存到 money_chart.png");

    Ok(())
}

use std::cell::RefCell;
use std::collections::HashMap;
use std::fs::File;
use std::io::{BufRead, BufReader};
use std::rc::Rc;
use std::str::FromStr;

use plotters::prelude::*;

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
