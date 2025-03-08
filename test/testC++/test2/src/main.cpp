#include <bits/stdc++.h>
using namespace std;

int main() {
    std::cout.precision(2);
    std::cout<<std::fixed;
    int dx=15,dy=17;
    int width=343720*2,height=233333*2;
    int dt=std::lcm(dx,width)/dx;
    for(int t=dt;;t+=dt){
        if(t*dy%height==0){
            std::cout<<std::hypot(t*dx,t*dy);
            break;
        }
    }
}