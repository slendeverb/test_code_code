impl Solution {
    pub fn lca_deepest_leaves(
        root: Option<Rc<RefCell<TreeNode>>>,
    ) -> Option<Rc<RefCell<TreeNode>>> {
        let mut ans = None;
        let mut max_depth = -1;

        fn dfs(
            node: &Option<Rc<RefCell<TreeNode>>>,
            depth: i32,
            max_depth: &mut i32,
            ans: &mut Option<Rc<RefCell<TreeNode>>>,
        ) -> i32 {
            if let Some(node) = node {
                let x = node.borrow();
                let left_max_depth = dfs(&x.left, depth + 1, max_depth, ans);
                let right_max_depth = dfs(&x.right, depth + 1, max_depth, ans);
                if left_max_depth == right_max_depth && left_max_depth == *max_depth {
                    *ans = Some(node.clone());
                }
                left_max_depth.max(right_max_depth)
            } else {
                *max_depth = (*max_depth).max(depth);
                depth
            }
        }

        dfs(&root, 0, &mut max_depth, &mut ans);
        ans
    }
}

#[allow(dead_code)]
struct Solution {}

fn main() {
    let input = "[0,1,2,3,4,5,6,7,8,9,10,11,12,13]";
    let nums = parse_tree_str::<i64>(input);
    let root = build_tree(&nums);
    let result = Solution::lca_deepest_leaves(root);
    println!("{:#?}", result);
}

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
            if part == "null" {
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
