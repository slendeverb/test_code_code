#include <iostream>
using namespace std;
#include <vector>
int main()
{
    int n = 0;
    int m = 0;
    int c = 0;
    cin >> n >> m >> c;
    vector<int> b(m + 1, 0);
    vector<vector<int>> a(n + 1, vector<int>(m + 1, 0));
    int i = 0;
    for (i = 0; i < m; i++)
    {
        cin >> b[i];
    }
    for (i = 0; i < n; i++)
    {
        int j = 0;
        for (j = 0; j < m; j++)
        {
            cin >> a[i][j];
        }
    }
    int count = 0;
    for (i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = 0; j < m; j++)
        {
            sum += b[j] * a[i][j];
        }
        sum += c;
        if (sum > 0)
        {
            count++;
        }
    }
    cout << count << endl;
    return 0;
}