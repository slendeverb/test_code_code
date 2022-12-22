#include<iostream>
using namespace std;

int main()
{
    FILE* pf1=fopen("file1.txt","w");
    if(pf1==NULL)
    {
        perror("fopen");
        return 1;
    }
    return 0;
}