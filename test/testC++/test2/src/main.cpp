// #include "header.h"
#include <bits/stdc++.h>

class Solution {
   public:
    std::string destCity(std::vector<std::vector<std::string>>& paths) {
        std::map<std::string, bool> dest;
        std::string res;
        for (const auto& path : paths) {
            dest[path[0]] = false;
            if(!dest.contains(path[1])){
                dest[path[1]]=true;
            }
        }
        for (const auto& x : dest) {
            if (x.second == true) {
                res = x.first;
            }
        }
        return res;
    }
};

int main(int argc, char** argv) {
    std::vector<std::vector<std::string>> paths{
        {"London", "New York"}, {"New York", "Lima"}, {"Lima", "Sao Paulo"}};
    std::cout<<std::format("{}\n",Solution{}.destCity(paths));
}