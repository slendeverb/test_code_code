#include <map>
#include <algorithm>
#include <cmath>
using namespace std;

long long exBSGS(long long a, long long b, long long p)
{
    map<long long, long long> Map_bsgs;
    // 可以改成unorderedmap
    a %= p, b %= p;
    if (b == 1 || p == 1)
        return 0;
    long long cnt = 0, add = 1;
    for (long long d = __gcd(a, p); (d ^ 1); d = __gcd(a, p))
    {
        if (b % d)
            return -1;
        b /= d, p /= d, cnt++;
        add = (a / d) * add % p;
        if (add == b)
            return cnt;
    }
    Map_bsgs.clear();
    long long t = ceil(sqrt(p));
    long long a_t = 1;
    for (long long i = 0; i <= t - 1; i++, a_t = a_t * a % p)
        Map_bsgs[b * a_t % p] = i;
    for (long long i = 0, now = add; i <= t; i++, now = now * a_t % p)
        if (Map_bsgs.find(now) != Map_bsgs.end())
            if (i * t - Map_bsgs[now] >= 0)
                return i * t - Map_bsgs[now] + cnt;
    return -1;
}