#include<stdio.h>
#include<stdlib.h>
int main()
{
	int n=0;
	int i=0;
	scanf("%d",&n);
	if(n>0 && n<1000)
	{
		int arr[1000]={0};
		for(i=0;i<n;i++)
		{
			getchar();
			scanf("%d",&arr[i]);
			if(arr[i]<0 || arr[i]>1000)
			{
				exit(0);
			}
		}
		int tmp=arr[0];
		for(i=0;i<n;i++)
		{
			if(arr[i]<arr[i+1])
			{
				tmp=arr[i+1];
			}
		}
		printf("%d",tmp);
	}
	return 0;
}