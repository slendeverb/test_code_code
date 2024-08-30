#include <bits/stdc++.h>

class CmpPair{
public:
    bool operator()(const std::pair<std::string,int>& x,const std::pair<std::string,int>& y) const {
        if(x.second==y.second){
            return x.first>y.first;
        }
        return x.second>y.second;
    }
};

void solve() {
    std::map<std::string,int> key_word;
    std::filesystem::path Marcille_meme{"D:/BaiduNetDiskDownload/玛露西尔表情包"};
    std::filesystem::directory_iterator Marcille_meme_iterator{Marcille_meme};
    for (auto& it : Marcille_meme_iterator) {
        if (it.is_directory()) {
            continue;
        }
        std::string it_stem{it.path().stem().string()};
        std::string category{it_stem.substr(it_stem.find_last_of("-")+1)};
        while(std::isdigit(category.back())){
            category.pop_back();
        }
        key_word[category]++;
    }
    std::vector<std::pair<std::string,int>> vec{key_word.begin(),key_word.end()};
    std::sort(vec.begin(),vec.end(),CmpPair{});
    for (auto& it : vec) {
        std::cout << it.first<<" "<<it.second << "\n";
    }
}

int main() {
    solve();
}