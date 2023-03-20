#include <iostream>
using namespace std;

const int N = 11;
int a[N][N];
int n;
long long k, ans;

int main()
{
    while (scanf("%d", &n) != EOF)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                cin >> a[i][j];
            }
        }
        cin >> k;
        k++;
        int tmp = k % 4;
        k /= 4;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                ans = (a[j][n + 1 - i] + a[n + 1 - i][n + 1 - j] + a[n + 1 - j][i] + a[i][j]);
                ans *= k;
                switch (tmp)
                {
                case 3:
                    ans += a[n + 1 - i][n + 1 - j];
                case 2:
                    ans += a[n + 1 - j][i];
                case 1:
                    ans += a[i][j];
                }
                cout << ans << " ";
            }
            cout << "\n";
        }
    }
    return 0;
}