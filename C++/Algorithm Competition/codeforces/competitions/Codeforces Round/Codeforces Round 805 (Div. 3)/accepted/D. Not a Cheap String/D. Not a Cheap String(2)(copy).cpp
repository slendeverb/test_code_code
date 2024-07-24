#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
const int N = 2e5 + 10;
map<char, int> mp; // map定义为 char 型和 int 型，用于判断输出
int a[N];
int main()
{
	int t;
	cin >> t; //输入测试数据组数
	while (t--)
	{
		string str; //定义一个字符串用于输入
		mp.clear(); //每组测试数据清除 map 中的所有数据
		cin >> str;
		int p;
		cin >> p;
		int sum = 0;
		int len = str.size(); //保存字符串长度
		for (int i = 0; i < len; i++)
		{
			a[i] = str[i] - 'a'; //用一个 int 型数组变形保存数据，便于排序
		}
		sort(a, a + len); //对 int 型数组进行升序排序
		for (int i = 0; i < len; i++)
		{
			if (sum + a[i] + 1 <= p) //如果加上该字符的总价格小于等于给定价格
			{						 //则将该数据变形为 char 类型保存记录
				sum += a[i] + 1;
				mp[a[i] + 'a']++;
			}
		}
		for (int i = 0; i < len; i++) //单次循环顺序遍历
		{
			if (mp[str[i]] != 0) //如果 map 中记录了该字符，则输出该字符
			{
				cout << str[i];
				mp[str[i]]--; //每输出一次，对应的字符个数 -1
			}
		}
		cout << endl;
	}
	return 0;
}