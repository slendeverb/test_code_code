#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int maxn = 1e5 + 10;
vector<string> v;
int Next[maxn];

void Get_Next(string sub, int len)
{
    int i = 0, j = -1;
    Next[0] = -1;
    while (i < len)
    {
        if (~j && sub[i] != sub[j])
            j = Next[j];
        else
            Next[++i] = ++j;
    }
}
int KMP(string s, int lena, string sub, int lenb)
{
    Get_Next(sub, lenb);
    int i = 0, j = 0;
    while (i < lena)
    {
        if (~j && s[i] != sub[j])
            j = Next[j];
        else
            i++, j++;
        if (j >= lenb)
        {
            j = Next[j];
            return i - lenb;
        }
    }
    return -1;
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        v.clear();
        for (int i = 1; i <= n; i++)
        {
            string tmp;
            cin >> tmp;
            v.push_back(tmp);
        }
        int q;
        cin >> q;
        int x, y;
        while (q--)
        {
            cin >> x >> y;
            x--, y--;
            string sx = v[x] + v[x];
            string sy = v[y];
            int ret = KMP(sx, sx.size(), sy, sy.size());
            if (ret != -1)
            {
                cout << "Yes\n";
            }
            else
            {
                cout << "No\n";
            }
        }
    }
    cout.flush();
    return 0;
}