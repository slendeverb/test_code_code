#include <iostream>
#include <print>
#include <atomic>
#include <thread>

void foo1(int i){
    std::println("{} {}","I love progarmming.",i);
}

void solve() {
    std::thread t1{foo1,0};
    
    t1.join();
}

int main() {
    solve();
    return 0;
}