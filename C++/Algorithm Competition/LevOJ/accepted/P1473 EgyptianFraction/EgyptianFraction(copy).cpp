#include <iostream>
#include <cmath>
#include <cstring>
#include <set>
using namespace std;

const int maxn = 100500;

long long num_tests, target_num, target_den, max_depth, found;
long long numerators[maxn], temp[maxn], p, q, fractions[maxn];
set<long long> prohibited_nums;

int is_solution_valid()
{
    for (int i = max_depth; i >= 1; i--)
    {
        if (numerators[i] != fractions[i])
        {
            if (numerators[i] == 0)
                return 0;
            if (numerators[i] > fractions[i])
                return 0;
            return 1;
        }
    }
    return 1;
}

long long gcd(long long a, long long b)
{
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

void dfs(int depth, long long numerator, long long denominator, long long prev)
{
    long long i;
    if (depth == max_depth)
    {
        if (denominator % numerator || prohibited_nums.count(denominator / numerator))
            return;
        fractions[depth] = denominator / numerator;
        if (!is_solution_valid())
            memcpy(numerators, fractions, sizeof(fractions));
        found = 1;
        return;
    }
    for (i = max(prev, denominator / numerator + 1);; i++)
    {
        if (prohibited_nums.count(i))
            continue;
        if (numerator * i >= denominator * (max_depth - depth + 1))
            return;
        long long new_numerator = numerator * i - denominator, new_denominator = denominator * i;
        long long divisor = gcd(new_numerator, new_denominator);
        fractions[depth] = i;
        dfs(depth + 1, new_numerator / divisor, new_denominator / divisor, i + 1);
    }
    return;
}

int main()
{
    int i, j;
    long long p, q;
    while (cin >> p >> q)
    {
        prohibited_nums.clear();
        prohibited_nums.insert(q);
        for (max_depth = 2;; max_depth++)
        {
            memset(numerators, 0, sizeof(numerators));
            dfs(1, p, q, q / p + 1);
            if (found)
                break;
        }
        cout << "1/" << numerators[1];
        for (j = 2; j <= max_depth; j++)
            cout << "+1/" << numerators[j];
        cout << "\n";
        memset(numerators, 0, sizeof(numerators));
        found = 0;
    }
    return 0;
}
