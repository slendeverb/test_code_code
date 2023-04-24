#include <iostream>
#include <string>

using namespace std;

int main()
{
    string str;
    cin >> str;
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int start, end;
        string before, after;
        cin >> start >> end >> before >> after;

        string clipboard = str.substr(start - 1, end - start + 1);
        str.erase(start - 1, end - start + 1);

        size_t pos = str.find(before + after);
        if (pos != string::npos)
        {
            str.insert(pos + before.size(), clipboard);
        }
        else
        {
            str += clipboard;
        }
    }

    cout << str << endl;

    return 0;
}