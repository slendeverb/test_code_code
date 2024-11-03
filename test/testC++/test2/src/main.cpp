#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        int n=price.size();
        std::map<std::vector<int>,int> memo;
        std::vector<std::vector<int>> filterSpecial;
        for(auto& sp:special){
            int totalCount=0,totalPrice=0;
            for(int i=0;i<n;i++){
                totalCount+=sp[i];
                totalPrice+=price[i]*sp[i];
            }
            if(totalCount>0&&totalPrice>sp[n]){
                filterSpecial.push_back(sp);
            }
        }

        auto dfs=[&](auto&& self,std::vector<int>& currentNeeds){
            if(memo.count(currentNeeds)){
                return memo[currentNeeds];
            }
            int minPrice=0;
            for(int i=0;i<n;i++){
                minPrice+=currentNeeds[i]*price[i];
            }
            for(auto& currentSpecial:filterSpecial){
                int specialPrice=currentSpecial[n];
                std::vector<int> nextNeeds;
                for(int i=0;i<n;i++){
                    if(currentSpecial[i]>currentNeeds[i]){
                        break;
                    }
                    nextNeeds.emplace_back(currentNeeds[i]-currentSpecial[i]);
                }
                if(nextNeeds.size()==n){
                    minPrice=std::min(minPrice,self(self,nextNeeds)+specialPrice);
                }
            }
            memo[currentNeeds]=minPrice;
            return memo[currentNeeds];
        };

        return dfs(dfs,needs);
    }
};

int main(){
    
}