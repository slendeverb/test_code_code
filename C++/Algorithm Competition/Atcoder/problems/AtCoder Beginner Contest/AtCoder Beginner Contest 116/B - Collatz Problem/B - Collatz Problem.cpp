#include <iostream>
using namespace std;
#define N 1000

int main()
{
    int s = 0;
    cin >> s;
    int arr[N] = {0};
    arr[0] = s;
    for (int i = 0; i < N - 1; i++)
    {
        if (arr[i] % 2 == 0)
        {
            arr[i + 1] = arr[i] / 2;
        }
        else
        {
            arr[i + 1] = arr[i] * 3 + 1;
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            if (arr[j] == arr[i])
            {
                cout << j + 1 << endl;
                goto End;
            }
        }
    }
End:
    return 0;
}