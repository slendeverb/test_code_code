#include "header.h"
using namespace std;

class Solution {
public:
    int numberOfPairs(vector<vector<int>>& points) {
        int ans=0;
        std::ranges::sort(points,{},[](auto& p){return std::pair{p[0],-p[1]};});
        int n=points.size();
        for(int i=0;i<n;i++){
            int y1=points[i][1];
            int max_y=INT_MIN;
            for(int j=i+1;j<n;j++){
                int y2=points[j][1];
                if(y2<=y1 && y2>max_y){
                    max_y=y2;
                    ans++;
                }
                if(max_y==y1){
                    break;
                }
            }
        }
        return ans;
    }
};

int main() {
    std::vector<std::vector<int>> points{{6,2},{4,4},{2,6}};
    auto result=Solution{}.numberOfPairs(points);
    std::print("{}\n",result);
}