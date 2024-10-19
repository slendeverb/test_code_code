#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minOperations(vector<int>&& nums) {
        int k=0;
        for(const auto& x:nums){
            if(x==k%2){
                k++;
            }
        }
        return k;
    }
};

int main(int argc, char** argv) {
    auto start = std::chrono::steady_clock::now();
    auto obj=Solution{};
    auto ans=obj.minOperations({0,1,1,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1});
    std::println("{}",ans);
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::format("\n{}\n", duration);
}