#include <iostream>
using namespace std;

const int maxn = 1e4 + 10;

struct cor
{
    int x, y;
} c[maxn];

int main()
{
    int n;
    cin >> n;
    for(int i=1;i<=n;i++)
    {
        cin>>c[i].x>>c[i].y;
    }
    
    return 0;
}