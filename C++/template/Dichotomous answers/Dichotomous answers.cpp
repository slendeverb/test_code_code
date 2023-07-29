bool check(int mid)
{
    //
    return;
}

int main()
{
    //
    long long l, r, mid, ans;
    while (l <= r)
    {
        mid = (l + r) >> 1;
        if (check(mid))
        {
            r = mid - 1;
            ans = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    //
    return 0;
}