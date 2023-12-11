#include <stdlib.h>
#include <windows.h>
#include <algorithm>
#include <array>
#include <charconv>
#include <cmath>
#include <compare>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <format>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <locale>
#include <map>
#include <memory>
#include <numbers>
#include <optional>
#include <set>
#include <span>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
//
using namespace std;
class B0{
    public:
        B0(int x=0){b0=x;} 
         int b0;
};
class B1:virtual public B0{ 
    public:
        B1(int x,int y):B0(x){b1=y;} 
        int b1; 
};
class B2: virtual public B0{ 
    public:
        B2(int x){b2=x;} 
        int b2; 
};
class D: public B1,public B2{ 
        int d;
    public:
        D(int a,int b,int c,int d):B0(a),B1(a,b),B2(c),d(d){ }
        void f(){cout<<b0<<b1<<b2<<d<<endl;} 
};
void solve()
{
    B1 b1(2,4); cout<<b1.b0<<b1.b1;
    B2 b2(6); cout<<b2.b0<<b2.b2<<endl;
    D d(1,2,3,4); d.f();
}

int main()
{
    clock_t startTime{clock()};
    solve();
    clock_t endTime{clock()};
    std::cout << "\n运行时间: " << endTime - startTime << std::endl;
    return 0;
}
