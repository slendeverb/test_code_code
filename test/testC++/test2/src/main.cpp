// #include "header.h"
#include <bits/stdc++.h>

class Solution{
public:
    int longestContinuousSubstring(std::string s){
        size_t size=s.size();
        if(size==1){
            return 1;
        }
        int ans=1,temp=1;
        for(int i=1;i<size;i++){
            if(s[i]==s[i-1]+1){
                temp++;
            }
            else{
                temp=1;
            }
            ans=std::max(ans,temp);
        }
        return ans;
    }
};

int main(int argc, char** argv) {
    std::string s="abcdefgijk";
    Solution so;
    std::cout<<so.longestContinuousSubstring(s);
}