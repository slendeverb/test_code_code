#include <iostream>
#include <cstdlib>
using namespace std;

int a[100], maxx, minn, cnt, sum, len, v[100];

bool cmp(int x, int y)
{
    return x > y;
}

void dfs(int stick_num_left, int pos_stick_len, int len, int max_stick_len_now)
{
    if (stick_num_left == 0)
    {
        cout << len << "\n";
        exit(0);
    }
    if (pos_stick_len == len)
    {
        dfs(stick_num_left - 1, 0, len, maxx);
        return;
    }
    for (int i = max_stick_len_now; i >= minn; i--)
    {
        if (v[i] && i + pos_stick_len <= len)
        {
            v[i]--;
            dfs(stick_num_left, pos_stick_len + i, len, i);
            v[i]++;
            if (pos_stick_len == 0 || pos_stick_len + i == len)
            {
                break;
            }
        }
    }
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        if (x <= 50)
        {
            a[++cnt] = x;
            maxx = max(x, maxx);
            minn = min(x, minn);
            sum += x;
            v[x]++;
        }
    }
    int tmp = sum / 2;
    for (int i = maxx; i <= tmp; i++)
    {
        if (sum % i == 0)
        {
            dfs(sum / i, 0, i, maxx);
        }
    }
    cout << sum << "\n";
    return 0;
}