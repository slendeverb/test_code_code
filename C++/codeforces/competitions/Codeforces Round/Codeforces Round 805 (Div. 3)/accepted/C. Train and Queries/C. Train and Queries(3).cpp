#include <iostream>
#include <map>
using namespace std;

int main()
{
    int t = 0;
    cin >> t;
    while (t--)
    {
        int n = 0, k = 0;
        cin >> n >> k;
        map<int, int> mstart;
        map<int, int> mend;
        int i = 0;
        for (i = 1; i <= n; i++)
        {
            int tmp = 0;
            cin >> tmp;
            if (mstart[tmp] == 0)
            {
                mstart[tmp] = i;
            }
            mend[tmp] = i;
        }
        for (i = 1; i <= k; i++)
        {
            int left = 0, right = 0;
            cin >> left >> right;
            if (mstart[right] == 0 || mend[left] == 0)
            {
                cout << "NO" << endl;
            }
            else
            {
                if (mend[right] > mstart[left])
                {
                    cout << "YES" << endl;
                }
                else
                {
                    cout << "NO" << endl;
                }
            }
        }
    }
    return 0;
}