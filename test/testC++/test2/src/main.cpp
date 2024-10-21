#include <bits/stdc++.h>
using namespace std;



int main(int argc, char** argv) {
    auto start=std::chrono::steady_clock::now();
    
    auto end=std::chrono::steady_clock::now();
    auto duration=std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    std::cout<<std::format("\n{}\n",duration);
}