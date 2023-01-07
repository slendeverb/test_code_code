#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

string pos, password, End;
unordered_map<string, int> ans;
int step[20][4] = {{1, 0, 0, 0}, {-1, 0, 0, 0}, {0, 1, 0, 0}, {0, -1, 0, 0}, {0, 0, 1, 0}, {0, 0, -1, 0}, {0, 0, 0, 1}, {0, 0, 0, -1}, {1, 1, 0, 0}, {-1, -1, 0, 0}, {0, 1, 1, 0}, {0, -1, -1, 0}, {0, 0, 1, 1}, {0, 0, -1, -1}, {0, 1, 1, 1}, {0, -1, -1, -1}, {1, 1, 1, 0}, {-1, -1, -1, 0}, {1, 1, 1, 1}, {-1, -1, -1, -1}};

bool check_s(string s)
{
    for (int i = 0; i < 4; i++)
    {
        if (s[i] < '0' || s[i] > '9')
        {
            return false;
        }
    }
    return true;
}

void bfs()
{
    queue<string> q;
    string start = "0000";
    q.push(start);
    while (!q.empty())
    {
        string tmp = q.front();
        int cnt = ans[tmp];
        q.pop();
        for (int i = 0; i < 20; i++)
        {
            string s = tmp;
            for (int j = 0; j < 4; j++)
            {
                s[j] = ((tmp[j] + step[i][j] - '0') + 10) % 10 + '0';
            }
            if (!check_s(s))
            {
                continue;
            }
            if (!ans.count(s))
            {
                ans[s] = cnt + 1;
                q.push(s);
            }
        }
    }
}

int main()
{
    int t;
    cin >> t;
    bfs();
    End.assign(4, '0');
    while (t--)
    {
        cin >> pos >> password;
        for (int i = 0; i < 4; i++)
        {
            End[i] = (pos[i] - password[i] + 10) % 10 + '0';
        }
        cout << ans[End] << "\n";
    }
    return 0;
}