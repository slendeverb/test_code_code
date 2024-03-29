#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

struct node
{
    std::string s;
    int count;

    bool operator<(const node &a) const
    {
        return count < a.count;
    }
};

void merge(std::string &raw, int start, int mid, int end, std::string &sorted, int &count)
{
    int i = start;
    int j = mid + 1;
    int k = start;

    while (i <= mid && j <= end)
    {
        if (raw[i] <= raw[j])
        {
            sorted[k++] = raw[i++];
        }
        else
        {
            sorted[k++] = raw[j++];
            count += mid - i + 1;
        }
    }
    while (i <= mid)
    {
        sorted[k++] = raw[i++];
    }
    while (j <= end)
    {
        sorted[k++] = raw[j++];
    }
    for (int i = start; i <= end; i++)
    {
        raw[i] = sorted[i];
    }
}

void mergeSort(std::string &raw, int start, int end, std::string &sorted, int &count)
{

    if (start >= end)
    {
        return;
    }
    int mid = ((end - start) >> 1) + start;
    mergeSort(raw, start, mid, sorted, count);
    mergeSort(raw, mid + 1, end, sorted, count);
    merge(raw, start, mid, end, sorted, count);
}

void DNASort(std::vector<node> &a)
{
    std::string raw;
    std::string sorted;
    int count;
    for (auto &x : a)
    {
        raw = x.s;
        sorted.resize(raw.size());
        count = 0;
        mergeSort(raw, 0, raw.size() - 1, sorted, count);
        x.count = count;
    }
    std::stable_sort(a.begin(), a.end());
}

int main()
{
    std::ifstream in{"../in.txt"};
    std::streambuf *oldIn = std::cin.rdbuf(in.rdbuf());
    std::ofstream out{"../out.txt"};
    std::streambuf *oldOut = std::cout.rdbuf(out.rdbuf());

    int n, m;
    std::cin >> n >> m;
    std::vector<node> a;
    a.reserve(m);

    std::string s;
    for (int i = 0; i < m; i++)
    {
        std::cin >> s;
        a.push_back(node{s, 0});
    }

    DNASort(a);
    for (auto &x : a)
    {
        std::cout << x.s << " " << x.count << "\n";
    }

    in.close();
    out.close();
    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);
    return 0;
}