#include <iostream>
using namespace std;

int hash_arr[1000001] = {0};
int hash2_arr[1000001] = {0};
int board[1000001] = {0};

int main()
{
    int n = 0;
    cin >> n;
    int i = 0;
    int j = 0;
    int max = 0;
    int flag = 1;
    for (i = 1; i <= n; i++)
    {
        cin >> board[i];
        hash_arr[board[i]]++;
    }
    for (i = 1; i <= n; i++)
    {
        if (hash_arr[i] >= 2)
        {
            flag = 0;
            hash2_arr[i] += hash_arr[i];
        }
    }
    if (flag)
    {
        cout << 0 << endl;
    }
    else
    {
        int ret = 0;
        for (i = 1; i <= n; i++)
        {
            int tmp = i + 1;
            if (hash2_arr[board[i]] != 0)
            {
                while (hash2_arr[board[i]] && tmp <= n)
                {
                    if (board[tmp] == board[i])
                    {
                        ret = tmp - i;
                        hash2_arr[board[i]]--;
                    }
                    tmp++;
                }
                if (ret > max)
                {
                    max = ret;
                }
            }
        }
        cout << max << endl;
    }
    return 0;
}