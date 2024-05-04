use std::collections::HashSet;

fn simple(i:&[u8])->usize{
    return i.windows(14)
        .position(|w|{
            return w.iter().collect::<HashSet<_>>().len()==14;
        })
        .map(|x| x+14)
        .unwrap();
}

fn main() {
    
}
