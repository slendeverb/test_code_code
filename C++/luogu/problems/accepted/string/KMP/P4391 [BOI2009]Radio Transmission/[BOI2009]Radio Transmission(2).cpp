#include <iostream>
#include <cstring>
using namespace std;

const int N = 1e6 + 10;
char a[N];
int Next[N];
int Size;

void cal_next(char a[], int Size)
{
    Next[1] = 0;
    for (int i = 2, j = 0; i <= Size; i++)
    {
        while (j && a[i] != a[j + 1])
        {
            j = Next[j];
        }
        if (a[i] == a[j + 1])
        {
            j++;
        }
        Next[i] = j;
    }
}

int main()
{
    cin >> Size;
    cin >> a + 1;
    cal_next(a, Size);
    cout << Size - Next[Size] << "\n";
    return 0;
}