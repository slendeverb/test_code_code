#include "header.h"
using namespace std;

int main() {
    std::cout<<"👈\n";
    std::vector<int> nums{3,4,5,6,7};
    std::cout<<std::ranges::fold_left(nums,0,std::bit_or{})<<(nums.size()-1);
}