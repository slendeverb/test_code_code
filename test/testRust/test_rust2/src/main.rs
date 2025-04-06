impl Solution {
    pub fn largest_divisible_subset(nums: Vec<i32>) -> Vec<i32> {
        let n = nums.len();
        let mut nums = nums;
        nums.sort();
        let mut f = vec![0; n];
        let mut from = vec![-1i32; n];
        let mut max_i = 0i32;

        for i in 0..n {
            for j in 0..i {
                if nums[i] % nums[j] == 0 && f[j] > f[i] {
                    f[i] = f[j];
                    from[i] = j as i32;
                }
            }
            f[i] += 1;
            if f[i] > f[max_i as usize] {
                max_i = i as i32;
            }
        }

        let mut path = Vec::new();
        let mut i = max_i;
        loop {
            if i < 0 {
                break;
            }
            path.push(nums[i as usize]);
            i = from[i as usize];
        }
        path
    }
}

fn main() {
    let nums = (1..=10000).collect::<Vec<i32>>();
    let result = Solution::largest_divisible_subset(nums);
    println!("{:?}", result.into_iter().rev().collect::<Vec<i32>>());
}

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

use std::cell::RefCell;
use std::rc::Rc;
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

use std::str::FromStr;
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
        let node = queue.pop_front().unwrap();
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
