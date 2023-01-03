#include<iostream>
using namespace std;

int gcd(int x,int y)
{
    if(x==0||y==0)
    {
        return x^y;
    }
    int t;
    while(t=x%y)
    {
        x=y;
        y=t;
    }
    return y;
}

int main()
{
    int a,b,n;
    cin>>a>>b>>n;
    while(1)
    {
        int x=gcd(a,n);
        if((n-x)<0)
        {
            cout<<1<<"\n";
            break;
        }
        else
        {
            n-=x;
        }
        int y=gcd(b,n);
        if((n-y)<0)
        {
            cout<<0<<"\n";
            break;
        }
        else
        {
            n-=y;
        }
    }
    return 0;
}