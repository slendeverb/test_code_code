#include "header.h"
using namespace std;

class Solution {
public:
    vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
        int n=grid.size();
        std::vector ans(n,std::vector<int>(n));
        int i=n-1,j=0;
        int cnt_diagonal=0;
        while(i>=0 && i<n && j>=0 && j<n){
            std::vector<int> temp_vec;
            int p=i,q=j;
            while(p<n && q<n){
                temp_vec.emplace_back(grid[p][q]);
                p++,q++;
            }
            cnt_diagonal++;
            if(cnt_diagonal<=n){
                std::sort(temp_vec.begin(),temp_vec.end(),std::greater<>{});
            }else{
                std::sort(temp_vec.begin(),temp_vec.end(),std::less<>{});
            }
            p=i,q=j;
            int cnt=0;
            while(p<n && q<n){
                ans[p][q]=temp_vec[cnt++];
                p++,q++;
            }

            if(i-1>=0){
                i--;
            }else{
                j++;
            }
        }
        return ans;
    }
};

int main() {
    
}