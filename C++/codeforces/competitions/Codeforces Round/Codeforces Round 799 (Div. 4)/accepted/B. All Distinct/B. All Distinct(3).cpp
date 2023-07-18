#include <iostream>
#include <set>
using namespace std;

int main()
{
    int t = 0;
    cin >> t;
    while (t--)
    {
        int n = 0;
        cin >> n;
        set<int> a;
        int x = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> x;
            a.insert(x);
        }
        if ((n - a.size()) % 2 == 0)
        {
            cout << a.size() << endl;
        }
        else
        {
            cout << a.size() - 1 << endl;
        }
    }
    return 0;
}