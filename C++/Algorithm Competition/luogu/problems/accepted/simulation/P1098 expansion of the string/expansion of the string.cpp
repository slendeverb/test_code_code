#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main()
{
    int p1, p2, p3;
    cin >> p1 >> p2 >> p3;
    string pos;
    cin >> pos;
    string ans = "";
    for (int i = 0; i < pos.size(); i++)
    {
        if (pos[i] != '-')
        {
            ans.push_back(pos[i]);
        }
        else
        {
            if (i == pos.size() - 1 || i == 0)
            {
                ans.push_back(pos[i]);
            }
            else
            {
                if (!(islower(pos[i - 1]) && islower(pos[i + 1]) || isdigit(pos[i - 1]) && isdigit(pos[i + 1])) || pos[i - 1] >= pos[i + 1])
                {
                    ans.push_back(pos[i]);
                    continue;
                }
                else if (pos[i + 1] - pos[i - 1] == 1)
                {
                    continue;
                }
                else
                {
                    if (p3 == 1)
                    {
                        char ch = pos[i - 1] + 1;
                        while (ch != pos[i + 1])
                        {
                            int tmp = p2;
                            while (tmp--)
                            {
                                if (p1 == 1)
                                {
                                    ans.push_back(ch);
                                }
                                else if (p1 == 2)
                                {
                                    if (islower(pos[i - 1]))
                                    {
                                        ans.push_back(ch - 32);
                                    }
                                    else
                                    {
                                        ans.push_back(ch);
                                    }
                                }
                                else
                                {
                                    ans.push_back('*');
                                }
                            }
                            ch++;
                        }
                    }
                    else
                    {
                        char ch = pos[i + 1] - 1;
                        while (ch != pos[i - 1])
                        {
                            int tmp = p2;
                            while (tmp--)
                            {
                                if (p1 == 1)
                                {
                                    ans.push_back(ch);
                                }
                                else if (p1 == 2)
                                {
                                    if (islower(pos[i - 1]))
                                    {
                                        ans.push_back(ch - 32);
                                    }
                                    else
                                    {
                                        ans.push_back(ch);
                                    }
                                }
                                else
                                {
                                    ans.push_back('*');
                                }
                            }
                            ch--;
                        }
                    }
                }
            }
        }
    }
    cout << ans << "\n";
    return 0;
}