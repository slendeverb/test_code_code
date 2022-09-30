#include<stdio.h>
int main()
{
    int i=0;
    int n=0;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        unsigned int a=0,b=0;
        char ch=0;
        scanf("%d%c%d",&a,&ch,&b);
        if(ch=='+')
        {
            printf("%d\n",a+b);
        }
        else if(ch=='-')
        {
            printf("%d\n",a-b);
        }
        else if(ch=='*')
        {
            printf("%d\n",a*b);
        }
        else if(ch=='/')
        {
            printf("%d\n",a/b);
        }
    }
    return 0;
}