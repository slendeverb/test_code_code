#include <iostream>
using namespace std;
#include <math.h>

int main()
{
    double n, m, a;
    cin >> n >> m >> a;
    double num = ceil(n / a) * ceil(m / a);
    printf("%.0lf\n", num);
    return 0;
}