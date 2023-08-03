#include <iostream>
using namespace std;

#define ls (pos << 1)
#define rs (pos << 1 | 1)

int n;
const int MAXN = 1e5 + 5;
int p[MAXN];

struct Segment_tree
{
    long long sum, mark;
    int l, r;
} s[MAXN << 2];

void pushup(int pos)
{
    s[pos].sum = s[ls].sum + s[rs].sum;
}

void pushdown(int pos)
{
}

void bulid_tree(int pos, int l, int r)
{
    s[pos].l = l;
    s[pos].r = r;

    if (l == r)
    {
        s[pos].sum = 0;
        return;
    }

    int mid = (l + r) >> 1;
    bulid_tree(ls, l, mid);
    bulid_tree(rs, mid + 1, r);
    pushup(pos);
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> p[i];
        }
        int Q;
        cin >> Q;
        int L, R;
        while (Q--)
        {
            cin >> L >> R;
        }
    }
    return 0;
}