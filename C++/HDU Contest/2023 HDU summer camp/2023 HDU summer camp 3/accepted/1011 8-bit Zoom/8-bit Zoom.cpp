#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

vector<string> picture;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, Z;
        cin >> n >> Z;
        picture.clear();
        for (int i = 0; i < n; i++)
        {
            string s;
            cin >> s;
            picture.push_back(s);
        }
        if (n * Z % 100 != 0)
        {
            cout << "error\n";
            continue;
        }
        else
        {
            int flag = 1;
            for (int i = 0; i < n; i++)
            {
                int cnt = 1;
                for (int j = 1; j < n; j++)
                {
                    if (picture[i][j] == picture[i][j - 1])
                    {
                        cnt++;
                    }
                    else
                    {
                        double tmp1 = cnt * (double)Z / 100;
                        int tmp2 = tmp1;
                        if (fabs((double)tmp2 - tmp1) < 1e-4)
                        {
                            cnt = 1;
                            continue;
                        }
                        else
                        {
                            cout << "error\n";
                            flag = 0;
                            break;
                        }
                    }
                }
                if (!flag)
                {
                    break;
                }
            }
            if (flag == 1)
            {
                int new_size = (double)Z / 100 * n;
                for (int i = 0; i < new_size; i++)
                {
                    for (int j = 0; j < new_size; j++)
                    {
                        cout << picture[i * 100 / Z][j * 100 / Z];
                    }
                    cout << "\n";
                }
            }
        }
    }
    return 0;
}