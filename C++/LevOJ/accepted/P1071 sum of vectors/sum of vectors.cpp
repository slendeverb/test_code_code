#include <iostream>
using namespace std;

int main()
{
    int n = 0;
    cin >> n;
    int *p1 = new int[n];
    int *p2 = new int[n];
    int i = 0;
    for (i = 0; i < n; i++)
    {
        cin >> p1[i];
    }
    for (i = 0; i < n; i++)
    {
        cin >> p2[i];
    }
    for (i = 0; i < n; i++)
    {
        int tmp = p1[i] + p2[i];
        printf("%d ", tmp);
    }
    return 0;
}