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
    std::string s="hello world wonderful world";
    std::unordered_map<std::string,int> map;
    std::stringstream ss{s};
    while(!ss.eof()){
        std::string temp;
        ss>>temp;
        ++map[temp];
    }
    for(const auto& [k,v]:map){
        std::println("{}: {}",k,v);
    }
}