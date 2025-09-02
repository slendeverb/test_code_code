#include "header.h"
using namespace std;

class Solution {
public:
    int numberOfPairs(vector<vector<int>>& points) {
        int ans=0;
        for(int i=0;i<points.size();i++){
            int x1=points[i][0];
            int y1=points[i][1];
            for(int j=0;j<points.size();j++){
                if(i==j){
                    continue;
                }
                int x2=points[j][0];
                int y2=points[j][1];
                if(x2>x1 || y2<y1){
                    continue;
                }
                bool has_inside=false;
                for(int k=0;k<points.size();k++){
                    if(i==k || j==k){
                        continue;
                    }
                    int x3=points[k][0];
                    int y3=points[k][1];
                    if(x3>=x2 && x3<=x1 && y3<=y2 && y3>=y1){
                        has_inside=true;
                        break;
                    }
                }
                if(has_inside){
                    continue;
                }else{
                    ans++;
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