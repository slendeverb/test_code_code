#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"

const int M=5e4+5;
int m;
std::string s;
std::stack<char> bracketsMatch;

struct QuestionMarkChangeToBracket
{
    int openingBracket,closingBracket;
    void input()
    {
        std::cin>>openingBracket>>closingBracket;
    }
}cost[M];

void solve()
{
    std::cin>>s;
    std::cin>>m;
    for(int i=1;i<=m;i++)
    {
        cost[i].input();
    }
    for(int i=0;i<s.size();i++)
    {
        if(s[i]=='(')
        {
            bracketsMatch.push(s[i]);
        }
        else if(s[i]=='?')
        {
            
        }
    }
}

signed main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    FILE *in = freopen("./test/in.txt", "r", stdin), *out = freopen("./test/out.txt", "w", stdout);
    int T = 1;
    // cin >> T;
    // init();
    while (T--)
    {
        solve();
    }
    return 0;
}