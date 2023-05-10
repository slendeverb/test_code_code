#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX_N = 1011;
int limit, best_ans;
bool found_solution;
int current_num[MAX_N], best_num[MAX_N];

void dfs(ll depth, ll numerator, ll denominator, ll prev)
{
    if (depth == limit + 1)
    {
        if (numerator == 0)
        {
            found_solution = true;
            if (current_num[limit] < best_num[limit])
            {
                for (ll i = 1; i <= limit; i++)
                    best_num[i] = current_num[i];
                best_ans = current_num[limit];
            }
        }
        return;
    }
    if ((denominator * (limit + 1 - depth)) / numerator > best_ans || current_num[depth] > best_ans)
        return;
    for (ll i = max(prev, denominator / numerator); i <= denominator * (limit + 1 - depth) / numerator; i++)
    {
        current_num[depth] = i;
        dfs(depth + 1, numerator * i - denominator, denominator * i, i + 1);
    }
}

int main()
{
    int a, b;
    while (cin >> a >> b)
    {
        for (limit = 1;; limit++)
        {
            best_num[limit] = 0x3f3f3f3f;
            best_ans = 0x3f3f3f3f;
            dfs(1, a, b, 1);
            if (found_solution)
                break;
        }
        bool isvalid = true;
        for (int i = 1; i <= limit; i++)
        {
            if (best_num[i] > 1000000 || best_num[i] == b)
            {
                isvalid = false;
                break;
            }
        }
        if (!isvalid)
        {
            cout << "No found!\n";
        }
        else
        {
            for (ll i = 1; i <= limit; i++)
            {
                if (i > 1)
                {
                    cout << '+';
                }
                cout << "1/" << best_num[i];
            }
            cout << "\n";
        }
    }
    return 0;
}
