#include <bits/stdc++.h>
using namespace std;

uint64_t factorial(uint64_t n){
    uint64_t res=1;
    for(uint64_t i=1;i<=n;i++){
        res*=i;
    }
    return res;
}

int main(){
	std::cout<<factorial(70)<<"\n";
}