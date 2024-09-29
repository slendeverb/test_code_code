// #include "header.h"
#include <bits/stdc++.h>

class Solution{
public:
    int timeRequiredToBuy(std::vector<int>& tickets,int k){
        int res=0;
        int tk=tickets[k];
        for(int i=0;i<tickets.size();i++){
            res+=std::min(tickets[i],tk-(i>k));
        }
        return res;
    }
};

int main(int argc, char** argv) {
    std::vector<int> tickets{5,1,1,1};
    int k=0;
    std::cout<<Solution{}.timeRequiredToBuy(tickets,k)<<"\n";
}