#include <iostream>
using namespace std;

int main()
{
    int n;
    while (scanf("%d", &n) != EOF)
    {
        for (int i = 1; i <= n; i++)
        {
            if (i * i <= n)
            {
                cout << i * i << " ";
            }
            else
            {
                break;
            }
        }
        cout << "\n";
    }
    return 0;
}