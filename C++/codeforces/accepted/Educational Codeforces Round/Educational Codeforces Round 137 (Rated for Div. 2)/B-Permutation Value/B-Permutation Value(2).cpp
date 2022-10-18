#include <iostream>
using namespace std;
//把相邻的数字放在数组两边
int main()
{
	int t = 0;
	cin >> t;
	int i = 0, j = 0;
	for (i = 0; i < t; i++)
	{
		int n = 0;
		cin >> n;
		int arr[51] = {0};
		int back = n;
		int num = 1;
		for (j = 1; num <= n;)
		{
			arr[j] = num;
			j++;
			num++;
			if (num > n)
			{
				break;
			}
			arr[back] = num;
			back--;
			num++;
		}
		for (j = 1; j <= n; j++)
		{
			cout << arr[j] << " ";
		}
		cout << endl;
	}
	return 0;
}