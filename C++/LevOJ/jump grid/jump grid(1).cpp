#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n = 0;
    cin >> n;
    vector<int> board(n + 1, 0);
    int i = 0;
    int j = 0;
    int max = 0;
    for (i = 1; i <= n; i++)
    {
        cin >> board[i];
        for (j = 1; j < i; j++)
        {
            if (board[i] == board[j])
            {
                if (i - j > max)
                {
                    max = i - j;
                    break;
                }
            }
        }
    }
    cout << max << endl;
    return 0;
}