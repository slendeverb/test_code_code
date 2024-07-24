#include <iostream>
#include <set>
using namespace std;

int n;
set<int> s;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        s.insert(x);
    }
    for (int i = 0; i <= n; i++)
    {
        if (s.count(i) == 0)
        {
            cout << i << "\n";
            break;
        }
    }
    return 0;
}