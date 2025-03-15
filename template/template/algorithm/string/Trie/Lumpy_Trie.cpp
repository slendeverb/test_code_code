#include <iostream>
#include <cstring>

#define clear(a) memset(a, 0, sizeof(a))
#define copy(a, b) memcpy(a, b, sizeof(a))
struct Lumpy_Tnode
{
    const char *pStr;
    //指向当前存储字符串首元素
    int length, isEnd;
    // length存储字符串的长度 isEnd代表是否是结尾节点
    Lumpy_Tnode *children[26];
    // 26个子节点
    inline Lumpy_Tnode()
    {
        pStr = 0, length = isEnd = 0, clear(children);
    }
    inline Lumpy_Tnode(const char *str, int len, int end)
    {
        pStr = str, length = len, isEnd = end, clear(children);
    }
    //构造函数
} mNode;

//插入操作:
//使用递归和循环,判断比较多,先看代码(看起来常数很大)

inline void insert(const char *str, int length, Lumpy_Tnode *bNode)
{
    // str是指针,指向当前插入字符串的第一个元素
    if (!length)
    {
        //字符串长度为0代表结尾
        //其实是为了优化代码美观,当作递归边界
        bNode->isEnd = 1;
        return;
    }
    int ch = str[0] - 'a';
    if (bNode->children[ch])
    {
        //子节点已存在
        bNode = bNode->children[ch];
        register int sptr = 0;
        while (sptr < length && sptr < bNode->length && bNode->pStr[sptr] == str[sptr])
            ++sptr;
        //循环来找当前字符串和节点存储的字符串最长前缀
        if (sptr != bNode->length)
        {
            //节点存储的字符串不是插入字符串的子串
            Lumpy_Tnode *nNode = new Lumpy_Tnode(bNode->pStr + sptr, bNode->length - sptr, bNode->isEnd);
            //拆树,运用字符串指针连续地址的特性来操作
            copy(nNode->children, bNode->children), clear(bNode->children);
            //继承原有子节点的各种信息
            bNode->isEnd = 0, bNode->children[bNode->pStr[sptr] - 'a'] = nNode;
            //清空原有节点,重新初始化
        }
        bNode->length = sptr;
        //更新当前节点存储的字符串长度,从而更改当前存储的字符串
        insert(str + sptr, length - sptr, bNode);
    }
    else
        bNode->children[ch] = new Lumpy_Tnode(str, length, 1);
    //不存在当前首字母的子节点,直接new并且赋值
    //因为是指针操作,所以不需要O(n)复制字符串,理论上复杂度O(3)?
    return;
}
//调用方式:insert(插入字符串, 字符串长度, Trie根节点);

//如果代码看懂了,第一反应可能认为指针操作有问题.
//的确插入的字符串在插入后就不能进行改变了,所以就只要开一个char[N][K]的数组来保存输入的字符串,K为最长字符串的长度.
//相比较空间复杂度总体仍然较小,其实是把原来每个节点存的char放到了一起,每个节点多了一个指针.(不过创建的节点更少了,所以浪费空间少)
//这其中其实有个很巧妙的事,树上的一条链可能指向的地址是连续的.仔细想了想,其实也有空间浪费,
//不管是节点上还是树上的最长公共前缀都只指向一个字符串,其他字符串中相同的字符占用的空间就永远浪费掉了,
//这句话不懂没事,因为这个浪费造成的影响很小.

//查找操作:

inline int find(const char *str, int length, Lumpy_Tnode *bNode)
{
    if (!length)
    {
        //递归到查找的字符串长度为0
        //判断当前节点是否为结尾,是否是第一次查询
        if (bNode->isEnd == 1)
            return bNode->isEnd++;
        return bNode->isEnd;
    }
    int ch = str[0] - 'a';
    if (bNode->children[ch])
    {
        bNode = bNode->children[ch];
        if (length < bNode->length)
            return 0;
        //自带剪枝,若当前查找字符串长度小于当前公共前缀,那么字典树中不存在当前查找的字符串
        register int sptr = 0;
        while (sptr < bNode->length && bNode->pStr[sptr] == str[sptr])
            ++sptr;
        if (sptr != bNode->length)
            return 0;
        //最长公共前缀必须是当前查找的字符串的子串
        return find(str + sptr, length - sptr, bNode);
    }
    return 0;
    //没有子节点,字典树中不存在当前查找的字符串
}
//调用方式:find(查询字符串, 字符串长度, Trie根节点);