#include <iostream>
#include <string>
using namespace std;

int main()
{
    long long t;
    while (cin >> t)
    {
        t /= 1000;
        long long s = t % 60;
        t /= 60;
        long long m = t % 60;
        t /= 60;
        long long h = t % 24;
        string S, M, H;
        if (s < 10)
            S = "0" + to_string(s);
        else
            S = to_string(s);
        if (m < 10)
            M = "0" + to_string(m);
        else
            M = to_string(m);
        if (h < 10)
            H = "0" + to_string(h);
        else
            H = to_string(h);
        string ans = H + ":" + M + ":" + S;
        cout << ans << "\n";
    }
    return 0;
}