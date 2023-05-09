#include <bits/stdc++.h>
using namespace std;

int n, m, max_depth;
int current_sol[10], best_sol[10];
bool found_solution;

void dfs(int depth, int start_value, int numerator, int denominator)
{
    if (depth > max_depth)
    {
        if (numerator == 0 && best_sol[max_depth] > current_sol[max_depth])
        {
            found_solution = false;
            for (int i = 1; i <= max_depth; ++i)
            {
                best_sol[i] = current_sol[i];
            }
        }
        return;
    }
    int left = ceil(double(denominator) / double(numerator));
    int right = min((max_depth - depth + 1) * left, best_sol[max_depth]);
    left = max(left, start_value);

    for (int i = left; i <= right; ++i)
    {
        int lcm_value = denominator * i / __gcd(denominator, i);
        current_sol[depth] = i;
        dfs(depth + 1, i + 1, numerator * (lcm_value / denominator) - (lcm_value / i), lcm_value);
    }
}

int main()
{
    memset(best_sol, 127, sizeof(best_sol));
    while (cin >> n >> m)

    {
        found_solution = true;
        while (found_solution)
        {
            ++max_depth;
            dfs(1, 1, n, m);
        }
        bool isvalid = true;
        for (int i = 1; i <= max_depth; i++)
        {
            if (best_sol[i] > 1000000 || best_sol[i] == m)
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
            for (int i = 1; i <= max_depth; ++i)
            {
                if (i > 1)
                    cout << '+';
                cout << "1/" << best_sol[i];
            }
            cout << "\n";
        }
    }
    return 0;
}
