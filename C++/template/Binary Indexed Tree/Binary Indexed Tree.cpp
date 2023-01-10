int n;
int a[1005], c[1005]; // 对应原数组和树状数组

int lowbit(int x)
{
    return x & (-x);
}

void updata(int i, int k) // 在i位置加上k
{
    while (i <= n)
    {
        c[i] += k;
        i += lowbit(i);
    }
}

int getsum(int i) // 求A[1 - i]的和
{
    int res = 0;
    while (i > 0)
    {
        res += c[i];
        i -= lowbit(i);
    }
    return res;
}