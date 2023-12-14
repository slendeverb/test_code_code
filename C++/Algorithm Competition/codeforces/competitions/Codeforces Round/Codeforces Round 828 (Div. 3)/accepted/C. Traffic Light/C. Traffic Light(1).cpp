#include <iostream>
using namespace std;

int main()
{
    int t = 0;
    cin >> t;
    while (t--)
    {
        int n = 0;
        char c = '0';
        scanf("%d %c", &n, &c);
        char s[200010] = {0};
        int arr[200010] = {0};
        scanf("%s", s);
        int i = 0, j = 0;
        int ans = 0;
        int len = 0;
        for (i = 0; i < n; i++)
        {
            if (s[i] == c)
            {
                arr[j] = i;
                j++;
                len++;
            }
        }
        for (int i = 0; i < len; i++)
        {
            int k = arr[i];
            int count = 0;
            for (int j = k;; j++)
            {
                if (j == n)
                {
                    j = 0;
                }
                if (s[j] != 'g')
                {
                    count++;
                }
                else
                {
                    break;
                }
            }
            ans = max(ans, count);
        }
        cout << ans << "\n";
    }
    return 0;
}