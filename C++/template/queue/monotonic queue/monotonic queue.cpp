#include <bits/stdc++.h>
using namespace std;
int q[1000005], p[1000005], a[1000005];
int n, k;
void minqueue()
{
    int head = 0, tail = -1;
    for (int i = 1; i <= n; i++)
    {
        while (head <= tail && q[tail] >= a[i])
            tail--;
        q[++tail] = a[i];
        p[tail] = i;
        while (p[head] <= i - k)
            head++;
        if (i >= k)
            printf("%d ", q[head]);
    }
    printf("\n");
}
void maxqueue()
{
    int head = 0, tail = -1;
    for (int i = 1; i <= n; i++)
    {
        while (head <= tail && q[tail] <= a[i])
            tail--;
        q[++tail] = a[i];
        p[tail] = i;
        while (p[head] <= i - k)
            head++;
        if (i >= k)
            printf("%d ", q[head]);
    }
    printf("\n");
}
int main()
{

    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    minqueue();
    maxqueue();
    return 0;
}