#include <bits/stdc++.h>
using namespace std;

#define IOS                      \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);
using LL = long long;
using ld = long double;
using ull = unsigned long long;
using PII = pair<int, int>;
using PLL = pair<long long, long long>;
using unl = __int128;
#define INF 1000000000
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
using UID = uniform_int_distribution<int>;

string A, B, C, s1, s2;

void solve()
{
    cin >> A >> s1 >> B >> s2 >> C;
    LL AA = 0, BB = 0, CC = 0;
    for (int i = 0; i < A.size(); i++)
    {
        AA = AA * 10 + A[i] - '0';
    }
    for (int i = 0; i < B.size(); i++)
    {
        BB = BB * 10 + B[i] - '0';
    }
    for (int i = 0; i < C.size(); i++)
    {
        CC = CC * 10 + C[i] - '0';
    }

    if (AA + BB == CC)
    {
        cout << "Yes\n";
        cout << AA << " + " << BB << " = " << CC << "\n";
    }
    else
    {
        if (AA + BB < CC)
        {
            for (int i = 0; i <= 9; i++)
            {
                string tmpB;
                for (double j = -0.5; j <= (double)B.size() + 0.5; j += 1.0)
                {
                    LL BBB = 0;
                    int posl = 0, posr = 0;
                    if (j < 0)
                    {
                        tmpB = to_string(i) + B;
                        for (int k = 0; k < tmpB.size(); k++)
                        {
                            BBB = BBB * 10 + tmpB[k] - '0';
                        }
                        if (AA + BBB == CC)
                        {
                            cout << "Yes\n";
                            cout << AA << " + " << BBB << " = " << CC << "\n";
                            return;
                        }
                    }
                    else if (j > B.size())
                    {
                        tmpB = B + to_string(i);
                        for (int k = 0; k < tmpB.size(); k++)
                        {
                            BBB = BBB * 10 + tmpB[k] - '0';
                        }
                        if (AA + BBB == CC)
                        {
                            cout << "Yes\n";
                            cout << AA << " + " << BBB << " = " << CC << "\n";
                            return;
                        }
                    }
                    else
                    {
                        posl = floor(j);
                        posr = ceil(j);
                        string tmpB1 = B.substr(0, posl + 1);
                        string tmpB2 = B.substr(posr);
                        tmpB = tmpB1 + to_string(i) + tmpB2;

                        for (int k = 0; k < tmpB.size(); k++)
                        {
                            BBB = BBB * 10 + tmpB[k] - '0';
                        }
                        if (AA + BBB == CC)
                        {
                            cout << "Yes\n";
                            cout << AA << " + " << BBB << " = " << CC << "\n";
                            return;
                        }
                    }
                }
            }

            for (int i = 0; i <= 9; i++)
            {
                string tmpA;
                for (double j = -0.5; j <= (double)A.size() + 0.5; j += 1.0)
                {
                    LL AAA = 0;
                    int posl = 0, posr = 0;
                    if (j < 0)
                    {
                        tmpA = to_string(i) + A;
                        for (int k = 0; k < tmpA.size(); k++)
                        {
                            AAA = AAA * 10 + tmpA[k] - '0';
                        }
                        if (AAA + BB == CC)
                        {
                            cout << "Yes\n";
                            cout << AAA << " + " << BB << " = " << CC << "\n";
                            return;
                        }
                    }
                    else if (j > A.size())
                    {
                        tmpA = A + to_string(i);
                        for (int k = 0; k < tmpA.size(); k++)
                        {
                            AAA = AAA * 10 + tmpA[k] - '0';
                        }
                        if (AAA + BB == CC)
                        {
                            cout << "Yes\n";
                            cout << AAA << " + " << BB << " = " << CC << "\n";
                            return;
                        }
                    }
                    else
                    {
                        posl = floor(j);
                        posr = ceil(j);
                        string tmpA1 = A.substr(0, posl + 1);
                        string tmpA2 = A.substr(posr);
                        tmpA = tmpA1 + to_string(i) + tmpA2;

                        for (int k = 0; k < tmpA.size(); k++)
                        {
                            AAA = AAA * 10 + tmpA[k] - '0';
                        }
                        if (AAA + BB == CC)
                        {
                            cout << "Yes\n";
                            cout << AAA << " + " << BB << " = " << CC << "\n";
                            return;
                        }
                    }
                }
            }
            cout << "No\n";
        }
        else
        {
            for (int i = 0; i <= 9; i++)
            {
                string tmpC;
                for (double j = -0.5; j <= (double)C.size() + 0.5; j += 1.0)
                {
                    LL CCC = 0;
                    int posl = 0, posr = 0;
                    if (j < 0)
                    {
                        tmpC = to_string(i) + C;
                        for (int k = 0; k < tmpC.size(); k++)
                        {
                            CCC = CCC * 10 + tmpC[k] - '0';
                        }
                        if (AA + BB == CCC)
                        {
                            cout << "Yes\n";
                            cout << AA << " + " << BB << " = " << CCC << "\n";
                            return;
                        }
                    }
                    else if (j > C.size())
                    {
                        tmpC = C + to_string(i);
                        for (int k = 0; k < tmpC.size(); k++)
                        {
                            CCC = CCC * 10 + tmpC[k] - '0';
                        }
                        if (AA + BB == CCC)
                        {
                            cout << "Yes\n";
                            cout << AA << " + " << BB << " = " << CCC << "\n";
                            return;
                        }
                    }
                    else
                    {
                        posl = floor(j);
                        posr = ceil(j);
                        string tmpC1 = C.substr(0, posl + 1);
                        string tmpC2 = C.substr(posr);
                        tmpC = tmpC1 + to_string(i) + tmpC2;

                        for (int k = 0; k < tmpC.size(); k++)
                        {
                            CCC = CCC * 10 + tmpC[k] - '0';
                        }
                        if (AA + BB == CCC)
                        {
                            cout << "Yes\n";
                            cout << AA << " + " << BB << " = " << CCC << "\n";
                            return;
                        }
                    }
                }
            }
            cout << "No\n";
        }
    }
}

signed main()
{
    // IOS;
    int T = 1;
    // cin >> T;
    // init();
    while (T--)
    {
        solve();
    }
    return 0;
}