#include "header.h"

class Solution{
public:
    long long distinctNames(std::vector<std::string>& ideas){
        std::unordered_set<std::string> groups[26];
        for(const auto& s:ideas){
            groups[s[0]-'a'].insert(s.substr(1));
        }
        int64_t res=0;
        for(int i=1;i<26;i++){
            for(int j=0;j<i;j++){
                int64_t m=0;
                for(const auto& s:groups[i]){
                    m+=groups[j].count(s);
                }
                res+=(int64_t)(groups[i].size()-m)*(groups[j].size()-m);
            }
        }
        return res*2;
    }

    Solution(){
        std::cin.tie(0)->sync_with_stdio(false);
        std::cout.tie(0)->sync_with_stdio(false);
    }
};

int main(int argc, char** argv) {
    std::vector<std::string> ideas{"coffee","donuts","time","toffee"};
    std::println("{}",Solution{}.distinctNames(ideas));
}