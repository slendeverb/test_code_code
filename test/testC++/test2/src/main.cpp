#include <bits/stdc++.h>

int main(int argc,char** argv){
    auto start_time=std::chrono::steady_clock::now();
    std::cout.tie(0)->sync_with_stdio(false);
    for(int i=0;i<1'0000'0;i++){
        std::cout<<i<<"\n";
    }
    auto end_time=std::chrono::steady_clock::now();
    auto duration=std::chrono::duration_cast<std::chrono::milliseconds>(end_time-start_time);
    std::cout<<duration<<"\n";
}