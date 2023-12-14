#include <iostream>
#include <string>
#include <vector>
using namespace std;

class KMP
{
    vector<int> nx;
    string b;

public:
    KMP(string b)
    {
        this->b = b;
        int n = b.length();
        int j = 0;
        nx.resize(n);
        for (int i = 1; i < n; i++)
        {
            while (j > 0 && b[i] != b[j])
                j = nx[j - 1];
            if (b[i] == b[j])
                j++;
            nx[i] = j;
        }
    }
    int find(string a) // a中出现多少次b
    {
        int n = b.length(), m = a.length();
        int j = 0;
        int ans = 0;
        for (int i = 0; i < m; i++)
        {
            while (j > 0 && a[i] != b[j])
                j = nx[j - 1];
            if (a[i] == b[j])
                j++;
            if (j == n)
            {
                ans++;
                j = nx[j - 1];
            }
        }
        return ans;
    }
};

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        string t;
        cin >> t;
        string ans0, ans1;
        ans0.assign(n, '0');
        ans1.assign(n, '1');
        KMP solve(t);
        if (solve.find(t + ans0 + t) == 2)
        {
            cout << ans0 << "\n";
        }
        else if (solve.find(t + ans1 + t) == 2)
        {
            cout << ans1 << "\n";
        }
        else
        {
            cout << "-1\n";
        }
    }
    return 0;
}