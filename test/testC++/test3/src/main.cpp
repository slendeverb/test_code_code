// #include "header.h"
#include <bits/stdc++.h>

void delete_point(const std::string& s){
    std::string ans;
    for(const auto c:s){
        if(c!='.'){
            ans.push_back(c);
        }
    }
    std::cout<<ans<<"\n";
}

int main(int argc,char** argv){
    std::string s;
    std::cin>>s;
    delete_point(s);
}