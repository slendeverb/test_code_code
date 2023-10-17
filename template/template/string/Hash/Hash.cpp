#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
const int b = 131;
long long hs[N], b_pow[N];
string s;
int n;

void initHash()
{
    b_pow[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        hs[i] = hs[i - 1] * b + s[i] - 'a' + 1;
        b_pow[i] = b_pow[i - 1] * b;
    }
}

long long getSub(int l, int r)
{
    return hs[r] - hs[l - 1] * b_pow[r - l + 1];
}