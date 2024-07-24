#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    int n = 0;
    cin >> n;
    string p, q;
    for (int i = 0; i < n; i++)
    {
        char tmp = 0;
        cin >> tmp;
        p += tmp;
    }
    for (int i = 0; i < n; i++)
    {
        char tmp = 0;
        cin >> tmp;
        q += tmp;
    }
    if (p == q)
    {
        cout << 0 << "\n";
    }
    else
    {
        if (p < q)
        {
            swap(p, q);
        }
        int ans = 0;
        while (next_permutation(q.begin(), q.end()))
        {
            if (p == q)
            {
                ans++;
                break;
            }
            else
            {
                ans++;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}