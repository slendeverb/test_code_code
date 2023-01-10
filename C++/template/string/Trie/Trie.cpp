#define re register

int top(1);
char str[60];
const int N=5e5+10;

struct Trie
{
    bool count;
    int next[26];
    bool exist; // exist表示此处是否为一个单词；count表示此单词是否已被查询。
} a[N];

inline void Trie_insert()
{ 
    //普通insert操作，将字符串一一加入字典中
    int num(0), root = 1;
    for (re int i = 0; str[i]; ++i)
    {
        num = str[i] - 'a';
        if (!a[root].next[num])
            a[root].next[num] = ++top;
        root = a[root].next[num];
    }
    a[root].exist = true;
    return;
}

inline int Trie_search()
{ 
    //普通search操作，查询是否存在该字符串
    int num(0), root = 1;
    for (re int i = 0; str[i]; ++i)
    {
        num = str[i] - 'a';
        if (!a[root].next[num])
            return 0; //若无法查询到后继的字母，直接退出
        root = a[root].next[num];
    }
    if (!a[root].exist)
        return 0; //若此处不存在字符串，返回“WRONG”
    else if (a[root].count)
        return 2;         //若此处字符串已被查询，返回“REPEAT”
    a[root].count = true; //若以上均不满足，说明合法
    return 1;             //此字符串标记为已查询，返回“OK”
}