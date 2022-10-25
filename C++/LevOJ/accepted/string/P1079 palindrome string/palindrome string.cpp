#include <iostream>
using namespace std;
#include <cstring>

void reverse(char *left, char *right)
{
    while (left < right)
    {
        char tmp = *left;
        *left = *right;
        *right = tmp;
        left++;
        right--;
    }
}
int main()
{
    int n = 0;
    cin >> n;
    getchar();
    while (n--)
    {
        char ch1[100000] = {0};
        char ch2[100000] = {0};
        int i = 0;
        while (1)
        {
            scanf("%c", &ch1[i]);
            ch2[i] = ch1[i];
            if (ch1[i] == '\n')
            {
                break;
            }
            i++;
        }
        reverse(&ch1[0], &ch1[i - 1]);
        if (strcmp(ch1, ch2) == 0)
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }
    return 0;
}