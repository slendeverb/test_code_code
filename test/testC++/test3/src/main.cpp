#include <iostream>
#include <print>
#include <torch/torch.h>

void solve() {
    std::println("{}",torch::cuda::is_available());
}

int main() {
    solve();
    return 0;
}