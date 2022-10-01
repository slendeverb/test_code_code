#include<stdio.h>
int main()
{
	int n=0;
	int i=0;
	scanf("%d",&n);
	int arr[1000]={0};
	for(i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
	}
	int tmp=arr[0];
	for(i=0;i<n;i++)
	{
		if(tmp<arr[i+1])
		{
			tmp=arr[i+1];
		}
	}
	printf("%d",tmp);			
	return 0;
}