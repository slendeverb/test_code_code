#include <iostream>
#include <torch/torch.h>

void solve(){
    std::cout<<torch::cuda::is_available()<<std::endl;
}

int main(){
    solve();
    return 0;
}