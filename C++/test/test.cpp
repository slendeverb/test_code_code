#include <iostream>
using namespace std;
#include<cstring>
int main()
{
    char a[20] = "ABCD\0EFG\0", b[] = "IJK";

    strcat(a, b);
    printf("%s\n", a);
    return 0;
}