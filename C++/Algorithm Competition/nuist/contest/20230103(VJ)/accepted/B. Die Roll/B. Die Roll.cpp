#include <iostream>
using namespace std;

int main()
{
    int y, w;
    cin >> y >> w;
    int num = 6 - max(y, w) + 1;
    int tot = 6;
    if (num % 2 == 0)
    {
        num /= 2;
        tot /= 2;
    }
    if (tot % num == 0)
    {
        tot /= num;
        num = 1;
    }
    cout << num << "/" << tot << "\n";
    return 0;
}