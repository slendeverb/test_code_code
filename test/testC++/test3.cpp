#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
using namespace std;

template <typename T>
struct ListNode
{
    T data{0};
    std::shared_ptr<ListNode> next{nullptr};

    ListNode(T data) : data{data} {}
};

template <typename T>
struct LinkList
{
    std::shared_ptr<ListNode<T>> head{nullptr};
    std::shared_ptr<ListNode<T>> tail{nullptr};

    void push_back(T data)
    {
        if (tail == nullptr)
        {
            tail = std::make_shared<ListNode<T>>(data);
            head = tail;
        }
        else
        {
            tail->next = std::make_shared<ListNode<T>>(data);
            tail = tail->next;
        }
    }
};

template <typename T>
class Graph
{
public:
    Graph()
    {
        m_graph = std::make_unique<LinkList<T>[]>(8);
        T u, v;
        while (cin >> u >> v)
        {
            m_graph[nodeNumber.at(u)].push_back(v);
        }
    }
    ~Graph() = default;
    void DFS(T s);

private:
    std::unique_ptr<LinkList<T>[]> m_graph{nullptr};
    bool visited[8] = {0};
    const std::unordered_map<T, int> nodeNumber{{'s', 0}, {'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}, {'f', 6}, {'t', 7}};
};

template <typename T>
void Graph<T>::DFS(T s)
{
    std::cout << s << " ";
    visited[nodeNumber.at(s)] = true;
    for (std::shared_ptr<ListNode<T>> nextVisit = m_graph[nodeNumber.at(s)].head; nextVisit != nullptr; nextVisit = nextVisit->next)
    {
        if (!visited[nodeNumber.at(nextVisit->data)])
        {
            DFS(nextVisit->data);
        }
    }
}

int main()
{
    std::istringstream inputString{"s a\ns b\na c\na e\nb c\nc d\nd e\nd t\ne f\nf t\n"};
    std::cin.rdbuf(inputString.rdbuf());

    Graph<char> graph;
    graph.DFS('s');
    return 0;
}