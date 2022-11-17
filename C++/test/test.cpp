#include <iostream>
using namespace std;

int main()
{
    char a[] = "morning";

    int i, j = 0;

    for (i = 1; i < 7; i++)

        if (a[j] < a[i])
            j = i;

    a[j] = a[7];

    puts(a);
    return 0;
}