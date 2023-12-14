#include <iostream>
#include <cstring>
using namespace std;

char s[50];
int top(1);

struct Trie
{
    bool count;
    int next[26];
    bool exist;
} a[500010];
inline void Trie_insert()
{
    int num(0), root = 1;
    for (int i = 0; s[i]; i++)
    {
        num = s[i] - 'a';
        if (!a[root].next[num])
        {
            a[root].next[num] = ++top;
        }
        root = a[root].next[num];
    }
    a[root].exist = true;
    return;
}
inline int Trie_search()
{
    int num(0), root = 1;
    for (int i = 0; s[i]; i++)
    {
        num = s[i] - 'a';
        if (!a[root].next[num])
        {
            return 0;
        }
        root = a[root].next[num];
    }
    if (!a[root].exist)
    {
        return 0;
    }
    else if (a[root].count)
    {
        return 2;
    }
    a[root].count = true;
    return 1;
}

int main()
{
    int n, m;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        memset(s, 0, sizeof(s));
        cin >> s;
        Trie_insert();
    }
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        memset(s, 0, sizeof(s));
        cin >> s;
        int tmp = Trie_search();
        if (tmp == 0)
        {
            cout << "WRONG"
                 << "\n";
        }
        else if (tmp == 1)
        {
            cout << "OK"
                 << "\n";
        }
        else if (tmp == 2)
        {
            cout << "REPEAT"
                 << "\n";
        }
    }
    return 0;
}