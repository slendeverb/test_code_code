#include <stdio.h>

int main()
{
    int t=0,m=0,n=0;
    scanf("%d",&t);
    int i=0,j=0;
    for(i=0;i<t;i++)
    {
        scanf("%d",&m);
        scanf("%d",&n);
        int* trap=new int[n];
        int* Fabo=new int[n];
        Fabo[1]=1;Fabo[2]=1;
        for(j=3;j<n;j++)
        {
            Fabo[j]=Fabo[j-1]+Fabo[j-2];
        }
        for(j=1;j<=n;j++)
        {
            scanf("%d",&trap[j]);
        }
        int n1=n,m1=m;
        
    }
    return 0;
}