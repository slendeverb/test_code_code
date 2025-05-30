#include "header.h"
using namespace std;

signed main() {
    std::string path{"C:/Users/slendeverb/Downloads/MAA-v4.24.0-win-x64/debug/gui.log"};
    std::ifstream in{path};
    std::string line;
    std::string regex{"已投资 "};
    std::map<std::string,int> count;
    while(std::getline(in,line)){
        size_t start_pos=line.find(regex);
        if(start_pos==std::string::npos){
            continue;
        }
        start_pos=line.find("(",start_pos);
        if(start_pos==std::string::npos){
            continue;
        }
        start_pos+=std::string{"("}.size();
        size_t end_pos=line.find(")");
        std::string added_money=line.substr(start_pos,end_pos-start_pos);
        if(added_money.find("+")==std::string::npos){
            continue;
        }
        added_money=added_money.substr(1);
        count[added_money]++;
    }
    for(const auto& [added_money,times]:count){
        std::println("added money: {}, times: {}",added_money,times);
    }
    in.close();
}