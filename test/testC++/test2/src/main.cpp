#include "header.h"
using namespace std;

class Solution {
public:
    int areaOfMaxDiagonal(vector<vector<int>>& dimensions) {
        double diagonal=0.0;
        int area=0;
        for(int i=0;i<dimensions.size();i++){
            int x=dimensions[i][0];
            int y=dimensions[i][1];
            double temp_diagonal=std::sqrt(x*x+y*y);
            if(std::fabs(temp_diagonal-diagonal)<1e-6){
                area=std::max(area,x*y);
            }else if(temp_diagonal>diagonal){
                diagonal=temp_diagonal;
                area=x*y;
            }
        }
        return area;
    }
};

int main() {
    
}