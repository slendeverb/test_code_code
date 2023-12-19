#include <iostream>
#include <memory>
#include <algorithm>

template <typename T>
class Queue
{
public:
    Queue()
    {
        m_elements = std::make_unique<T[]>(MAXQSIZE);
    }
    bool empty() const
    {
        return m_front == m_rear;
    }
    bool full() const
    {
        return (m_front - m_rear + MAXQSIZE) % MAXQSIZE == 1;
    }
    void push(const T &element)
    {
        if (full())
        {
            return;
        }
        m_elements[m_rear] = element;
        m_rear = (m_rear + 1 + MAXQSIZE) % MAXQSIZE;
    }
    void pop()
    {
        if (empty())
        {
            return;
        }
        m_front = (m_front + 1 + MAXQSIZE) % MAXQSIZE;
    }
    T front() const
    {
        return m_elements[m_front];
    }

private:
    const int MAXQSIZE{50000};
    int m_front{0};
    int m_rear{0};
    std::unique_ptr<T[]> m_elements;
};

struct Edge
{
    int v;
    std::shared_ptr<Edge> next{nullptr};

    Edge(int v) : v{v} {}
};

struct VillageNode
{
    int depth;
    std::shared_ptr<Edge> firstEdge;
    int father[20];
};

class Graph
{
    int vertexNum;
    int edgeNum;
    std::unique_ptr<VillageNode[]> village;

public:
    Graph(int n)
    {
        vertexNum = n;
        edgeNum = n - 1;
        village = std::make_unique<VillageNode[]>(vertexNum);
    }

    void create()
    {
        int u, v;
        std::shared_ptr<Edge> p, q;
        for (int i = 0; i < edgeNum; i++)
        {
            std::cin >> u >> v;
            p = std::make_shared<Edge>(u);
            q = std::make_shared<Edge>(v);
            if (village[u].firstEdge == nullptr)
            {
                village[u].firstEdge = q;
            }
            else
            {
                auto tmp = village[u].firstEdge;
                while (tmp->next != nullptr)
                {
                    tmp = tmp->next;
                }
                tmp->next = q;
            }
            if (village[v].firstEdge == nullptr)
            {
                village[v].firstEdge = p;
            }
            else
            {
                auto tmp = village[v].firstEdge;
                while (tmp->next != nullptr)
                {
                    tmp = tmp->next;
                }
                tmp->next = p;
            }
        }
    }

    void BFS()
    {
        Queue<int> q;
        village[0].depth = 0;
        village[0].father[0] = 0;
        q.push(0);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int i = 1; i < 20; i++) // u的第2^i个父亲结点等于u的第2^(i-1)个父亲结点的第2^(i-1)个父亲结点
            {
                village[u].father[i] = village[village[u].father[i - 1]].father[i - 1];
            }
            std::shared_ptr<Edge> p;
            for (p = village[u].firstEdge; p != nullptr; p = p->next)
            {
                int v = p->v;
                if (v == village[u].father[0]) // 因为存储的是双向边，所以防止再访问到已经访问过的父亲结点
                {
                    continue;
                }
                village[v].depth = village[u].depth + 1;
                village[v].father[0] = u;
                q.push(v);
            }
        }
    }

    int LCA(int u, int v)
    {
        if (village[u].depth > village[v].depth)
        {
            std::swap(u, v);
        }
        int depthDifference = village[v].depth - village[u].depth;
        int du = u, dv = v;
        for (int i = 0; depthDifference; depthDifference >>= 1, i++)
        {
            if (depthDifference & 1)
            {
                dv = village[dv].father[i];
            }
        }
        if (dv == du)
        {
            return du;
        }
        for (int i = 19; i >= 0; i--) // 不在同一结点却在同一深度，那就两个结点一起往上跳2^i单位
        {
            if (village[du].father[i] == village[dv].father[i]) // 如果会跳过了，则跳过这一步跳跃
            {
                continue;
            }
            du = village[du].father[i];
            dv = village[dv].father[i];
        }
        return village[du].father[0];
    }

    bool inPath(int a, int b, int c)
    {
        int vertexInAB = LCA(a, b);
        int endPointOfAC = LCA(a, c);
        int endPointOfBC = LCA(b, c);
        if (endPointOfAC == c && endPointOfBC == c) // 如果endPointOfAC == c并且endPointOfBC == c，说明c结点是a和b的公共祖先
        {
            if (vertexInAB == c) // 如果vertexInAB == c，说明c就是a和b的最近公共祖先,c必定在a和b的路径上
            {
                return true;
            }
            else // 如果vertexInAB != c，说明c不是a和b的最近公共祖先，a和b的路径上不包括c
            {
                return false;
            }
        }
        else if (endPointOfAC == c || endPointOfBC == c) // c是a的祖先或者是b的祖先，说明c在a到vertexInAB的路径上或者在b到vertexInAB的路径上
        {
            return true; // 此时c一定是a和b路径上的点
        }
        else
        {
            return false; // 如果c不是a的祖先，也不是b的祖先，则a和b的路径上不会经过c点
        }
    }
};

int main()
{
    int n, m;
    int a, b, c;
    while (std::cin >> n)
    {
        if (n == 0)
        {
            break;
        }
        Graph graph(n);
        graph.create();
        graph.BFS();
        std::cin >> m;
        while (m--)
        {
            std::cin >> a >> b >> c;
            bool isInPath = graph.inPath(a, b, c);
            if (isInPath)
            {
                std::cout << "Yes\n";
            }
            else
            {
                std::cout << "No\n";
            }
        }
    }
    return 0;
}