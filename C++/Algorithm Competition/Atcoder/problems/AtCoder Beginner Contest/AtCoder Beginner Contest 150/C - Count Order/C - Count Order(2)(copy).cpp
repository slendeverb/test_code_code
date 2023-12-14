//库函数next_permutation使用，支持vector,string

#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
const int N = 100100;
const int INF = 0x3f3f3f3f;
typedef pair<int, int> PII;

int n, m, s, d;

int main(void)
{
    cin >> n;
    string q, qq;
    char tmp;
    for (int i = 0; i < n; i++)
    {
        cin >> tmp;
        q += tmp;
    }
    for (int i = 0; i < n; i++)
    {
        cin >> tmp;
        qq += tmp;
    }
    if (q < qq)
        swap(q, qq);
    else if (q == qq)
    {
        cout << "0\n";
        return 0;
    }
    int ans = 1;
    while (next_permutation(qq.begin(), qq.end()))
    {
        if (q == qq)
            break;
        ans++;
    }
    cout << ans << endl;

    return 0;
}