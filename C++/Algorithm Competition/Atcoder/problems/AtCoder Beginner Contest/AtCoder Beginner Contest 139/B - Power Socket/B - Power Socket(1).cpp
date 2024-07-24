#include <iostream>
using namespace std;

int main()
{
    int a = 0, b = 0;
    cin >> a >> b;
    int tmp = b % a + 1;
    cout << tmp;
    return 0;
}