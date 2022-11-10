#include <iostream>
#include <string>

using namespace std;

int main()
{
    //数组a储存每个小写字母的出现次数
    int a[26] = {0};
    //储存字符串
    string arr;
    //储存最大出现次数
    int max = 0;
    //储存出现次数最大的字母
    char max_sp;
    //输入字符串
    cin >> arr;
    //对字母串中的每个字符计数
    for (int i = 0; i < arr.length(); i++)
    {
        a[arr[i] - 'a']++;
    }
    //找出最大出现次数，若正向遍历，则应a[i]>max，为了出现次数相同时，输出最小字典序的字符
    for (int i = 25; i >= 0; i--)
    {
        if (a[i] >= max)
        {
            max = a[i];
            max_sp = char(i + 'a');
        }
    }
    //找到出现次数最大的字典序最小的字母，输出它和它的出现次数
    cout << max_sp << endl;
    cout << max;

    return 0;
}