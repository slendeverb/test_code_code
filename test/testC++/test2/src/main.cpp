#include "header.h"

class Solution {
   public:
    int edgeScore(std::vector<int>& edges){
        int n=edges.size();
        std::vector<long long> score(n,0);
        for(int i=0;i<n;i++){
            score[edges[i]]+=i;
        }
        int ans=0;
        long long max=0;
        for(int i=0;i<n;i++){
            if(score[i]>max){
                max=score[i];
                ans=i;
            }
        }
        return ans;
    }
};

int main(int argc, char** argv) {
    std::vector<int> nums{1,0,0,0,0,7,7,5};
    auto ans = Solution{}.edgeScore(nums);
    std::println("{}",ans);
}