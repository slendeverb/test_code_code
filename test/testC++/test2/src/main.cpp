#include <bits/stdc++.h>

void solve() {
    size_t per_size=sizeof(unsigned char);
    size_t size = static_cast<unsigned char>(-1);
    int *buffer=nullptr;
    try{
        buffer=new int[size/per_size];
    }catch(const std::bad_alloc& e){
        std::cout<<e.what()<<" "<<__func__<<" "<<__LINE__<<"\n";
    }catch(const std::exception& e){
        std::cout<<e.what()<<" "<<__func__<<" "<<__LINE__<<"\n";
    }
    if(buffer!=nullptr){
        printf("%p\n",buffer);
        delete buffer;
        buffer=nullptr;
    }
}

int main() {
    solve();
}