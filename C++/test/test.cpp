#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

vector<int> tmp = {1, 2, 3, 4, 5, 6, 7, 8};
map<long long, long long> m;

bool judge(int before, int after)
{
    if (before <= tmp.size() / 2)
    {
        if (before < after)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (before > after)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

int main()
{
    long long sum = 0;
    do
    {
        int pos = 0;
        sum++;
        long long ans = 0;
        ans++;
        int before = 0;
        int after = 0;
        do
        {
            if (pos == tmp.size() - 1)
            {
                break;
            }
            before = tmp[pos++];
            after = tmp[pos];
            ans++;
            sum++;
        } while (judge(before, after));
        m[ans]++;
    } while (next_permutation(tmp.begin(), tmp.end()));
    long long p = 1;
    for (int i = 1; i <= tmp.size(); i++)
    {
        p *= i;
    }
    cout << sum << "\n";
    for (auto e : m)
    {
        cout << e.first << ' ' << e.second << "\n";
    }
    return 0;
}