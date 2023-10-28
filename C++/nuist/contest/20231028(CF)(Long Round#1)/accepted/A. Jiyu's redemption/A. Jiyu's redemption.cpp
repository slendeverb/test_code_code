#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"

int a, b;

void chessMove(int a, int b, vector<pair<int, int>> &chess)
{
    int pos = chess[a].first;
    int d = chess[a].second;
    int maxd = 0;
    for (int i = 1; i <= 3; i++)
    {
        if (i == a)
        {
            continue;
        }
        if (chess[i].first == pos + b)
        {
            maxd = max(maxd, chess[i].second);
        }
    }

    for (int i = 1; i <= 3; i++)
    {
        if (i == a)
        {
            continue;
        }
        if (chess[i].first == pos && chess[i].second > d)
        {
            chess[i].first = pos + b;
            chess[i].second = chess[i].second - (d - 1) + maxd;
        }
    }

    chess[a].first = pos + b;
    chess[a].second = maxd + 1;
}

void solve()
{
    vector<pair<int, int>> chess(4, pair<int, int>(0, 0));
    chess[1].first = 2, chess[1].second = 1;
    chess[2].first = 3, chess[2].second = 1;
    chess[3].first = 4, chess[3].second = 1;
    for (int i = 1; i <= 12; i++)
    {
        cin >> a >> b;
        chessMove(a, b, chess);

        //     for (int i = 1; i <= 3; i++)
        //     {
        //         cout << chess[i].first << " " << chess[i].second << endl;
        //     }
        //     cout << "......................\n";
    }

    if (chess[1].first == 9 && chess[2].first == 9 && chess[3].first == 9)
    {
        cout << "Y\n";
    }
    else
    {
        cout << "N\n";
    }
}

signed main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    freopen("C:/Users/slendeverb/Documents/code_code/test/in.txt", "r", stdin);
    freopen("C:/Users/slendeverb/Documents/code_code/test/out.txt", "w", stdout);
    int T = 1;
    cin >> T;
    // init();
    while (T--)
    {
        solve();
    }
    return 0;
}