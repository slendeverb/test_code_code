#include "header.h"

class Solution {
   public:
    bool reportSpam(std::vector<std::string>& message, std::vector<std::string>& bannedWords) {
        std::unordered_set<std::string> banned(bannedWords.begin(), bannedWords.end());
        int count = 0;
        for (const auto& s : message) {
            if (banned.contains(s) && ++count > 1) {
                return true;
            }
        }
        return false;
    }
};

int main(int argc, char** argv) {
    std::vector<std::string> v1{"123","456"};
    std::vector<int> v2{1,2};
    auto v3=std::views::zip(v1,v2)|std::ranges::to<std::map>();
    for(const auto& [key,val]:v3){
        std::println("key: {}, val: {}",key,val);
    }
}