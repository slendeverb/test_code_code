#include <stdio.h>

int count = 0;
int Kakutani(int a)
{
    if (a > 1)
    {
        if (a % 2 == 0)
        {
            count++;
            Kakutani(a / 2);
        }
        else
        {
            count++;
            Kakutani((3 * a + 1) / 2);
        }
    }
    return count;
}
int main()
{
    int a = 0;
    while (scanf("%d", &a) != EOF)
    {
        int ret = Kakutani(a);
        printf("%d\n", ret);
        count = 0;
    }
    return 0;
}