use std::collections::HashMap;

fn main() {
    let mut scores=HashMap::new();
    scores.insert(String::from("Blue"), 10);
    scores.insert(String::from("Yellow"), 50);

    let team_name=String::from("Red");
    let score=scores.get(&team_name);
    match score{
        Some(s) => {println!("{}",s)},
        None => {println!("team not exist")},
    };

    for (k,v) in &scores{
        println!("{}: {}",k,v);
    }
}
