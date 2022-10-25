#include <iostream>
using namespace std;
#include <math.h>

int isprime(int num)
{
    if (num == 2 || num == 3)
    {
        return 1;
    }
    if (num % 6 != 1 && num % 6 != 5)
    {
        return 0;
    }
    for (int i = 5; i <= floor(sqrt((double)num)); i += 6)
    {
        if (num % i == 0 || num % (i + 2) == 0)
        {
            return 0;
        }
    }
    return 1;
}
int main()
{
    int num = 0;
    while (scanf("%d", &num) != EOF)
    {
        int i = 0;
        int tmp = 2;
        int arr[1000] = {0};
        while (tmp <= num)
        {
            if (isprime(tmp))
            {
                arr[i] = tmp;
                i++;
            }
            tmp++;
        }
        i = 0;
        while (arr[i] != 0)
        {
            if (num % arr[i] == 0)
            {
                printf("%d ", arr[i]);
                num /= arr[i];
            }
            else
            {
                i++;
            }
        }
        cout << endl;
    }
    return 0;
}