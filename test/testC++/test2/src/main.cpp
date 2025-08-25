#include "header.h"
using namespace std;

class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        std::vector<int> ans;
        int i=0,j=0;
        int m=mat.size();
        int n=mat[0].size();
        while(i<m && j<n){
            while(i>=0){
                ans.emplace_back(mat[i][j]);
                if(i-1<0 || j+1>=n){
                    break;
                }
                i-=1;j+=1;
            }
            if(j+1<n){
                j+=1;
            }else if(i+1<m){
                i+=1;
            }else{
                break;
            }
            while(i<m){
                ans.emplace_back(mat[i][j]);
                if(i+1>=m || j-1<0){
                    break;
                }
                i+=1;j-=1;
            }
            if(i+1<m){
                i+=1;
            }else if(j+1<n){
                j+=1;
            }else{
                break;
            }
        }
        return ans;
    }
};

int main() {
    std::vector<std::vector<int>> mat{{1,2},{4,5},{7,8}};
    auto result=Solution{}.findDiagonalOrder(mat);
    for(int i=0;i<result.size();i++){
        std::cout<<std::format("{} ",result[i]);
    }
}