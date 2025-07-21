#include "header.h"
using namespace std;

class Solution {
public:
    vector<string> removeSubfolders(vector<string>& folder) {
        std::ranges::sort(folder);
        std::vector<std::string> ans{folder[0]};
        for(int i=1;i<folder.size();i++){
            std::string& s=folder[i];
            std::string& last=ans.back();
            if(!s.starts_with(last) || s[last.size()]!='/'){
                ans.emplace_back(s);
            }
        }
        return ans;
    }
};

int main() {
    std::vector<std::string> folder{"/a","/a/b","/c/d","/c/d/e","/c/f"};
    auto result=Solution{}.removeSubfolders(folder);
    for(const auto& x:result){
        std::cout<<std::format("{}\n",x);
    }
}