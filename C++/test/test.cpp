#include <iostream>
using namespace std;

template <typename ALL> void My_Swap(ALL &a, ALL &b)
{
    ALL tmp = a;
    a = b;
    b = tmp;
}

int main()
{
    int a = 0, b = 1;
    My_Swap(a, b);
    return 0;
}