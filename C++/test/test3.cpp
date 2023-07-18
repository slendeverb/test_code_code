void init_next(int n)
{
    for (int i = 0; i < n; i++)
    {
        Next[i] = 0;
    }
}

void cal_next(string s, int n)
{
    Next[0] = 0;
    int len = 0;
    int i = 1;
    while (i < n)
    {
        if (s[i] == s[len])
        {
            len++;
            Next[i] = len;
            i++;
        }
        else
        {
            if (len > 0)
            {
                len = Next[len - 1];
            }
            else
            {
                Next[i] = len;
                i++;
            }
        }
    }
    for (i = n - 1; i > 0; i--)
    {
        Next[i] = Next[i - 1];
    }
    Next[0] = -1;
}

int kmp_search(string s1, string s2)
{
    int n = s2.size();
    int m = s1.size();
    cal_next(s2, n);
    int i = 0, j = 0, flag = 0;
    while (i < m)
    {
        if (j == n - 1 && s1[i] == s2[j])
        {
            return i - j;
            flag = 1;
            j = Next[j];
        }
        if (s1[i] == s2[j])
        {
            i++;
            j++;
        }
        else
        {
            j = Next[j];
            if (j == -1)
            {
                i++;
                j++;
            }
        }
    }
    if (flag == 0)
    {
        return -1;
    }
    return 0;
}