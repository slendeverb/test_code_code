#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> maximumBeauty(vector<vector<int>>& items, vector<int>& queries) {
        std::ranges::sort(items,{},[](auto& item){return item[0];});
        std::vector<int> idx(queries.size());
        std::iota(idx.begin(),idx.end(),0);
        std::ranges::sort(idx,{},[&](int i){return queries[i];});

        std::vector<int> ans(queries.size());
        int max_beauty=0,j=0;
        for(int i:idx){
            int q=queries[i];
            while(j<items.size() && items[j][0]<=q){
                max_beauty=std::max(max_beauty,items[j][1]);
                j++;
            }
            ans[i]=max_beauty;
        }
        return ans;
    }
};

int main() {
    std::cout.precision(2);
    std::cout << std::fixed;
    int dx = 15, dy = 17;
    int width = 343720 * 2, height = 233333 * 2;
    int dt = std::lcm(dx, width) / dx;
    for (int t = dt;; t += dt) {
        if (t * dy % height == 0) {
            std::cout << std::hypot(t * dx, t * dy);
            break;
        }
    }
}