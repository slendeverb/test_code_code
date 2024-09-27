#include "header.h"

class Solution{
public:
    int takeCharacters(const std::string& s,int k){
        std::unordered_map<char,int> counter;
        for (const char c:s){
            counter[c]++;
        }
        if(counter['a']<k||counter['b']<k||counter['c']<k){
            return -1;
        }
        int max_length=0;
        int left=0;
        for(int right=0;right<s.size();right++){
            const char c=s[right];
            counter[c]--;
            while (counter[c]<k){
                counter[s[left]]++;
                left++;
            }
            max_length=std::max<int>(max_length,right-left+1);
        }
        return s.size()-max_length;
    }
};

int main(int argc,char** argv){
    const std::string s="aabaaaacaabc";
    const int k=2;
    std::println("{}",Solution{}.takeCharacters(s,k));
}