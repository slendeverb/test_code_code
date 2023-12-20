#include <iostream>
#include <memory>
#include <algorithm>

template <typename T>
class Queue
{
public:
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
    std::unique_ptr<T[]> m_elements{std::make_unique<T[]>(MAXQSIZE)};
};

struct Edge
{
    int v{0};
    std::shared_ptr<Edge> next{nullptr};

    Edge(int v) : v{v} {}
};

struct VillageNode
{
    int depth{0};
    std::shared_ptr<Edge> firstEdge{nullptr};
    int father[20] = {0};
};

class Graph
{
    int vertexNum{0};
    int edgeNum{0};
    std::unique_ptr<VillageNode[]> village{std::make_unique<VillageNode[]>(vertexNum)};
    std::unique_ptr<bool[]> visited{std::make_unique<bool[]>(vertexNum)};

public:
    Graph(int n) : vertexNum{n}, edgeNum{n - 1} {}

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
        visited[0] = true;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int i = 1; i < 20; i++)
            {
                village[u].father[i] = village[village[u].father[i - 1]].father[i - 1];
            }
            for (auto p = village[u].firstEdge; p != nullptr; p = p->next)
            {
                int v = p->v;
                if (visited[v])
                {
                    continue;
                }
                village[v].depth = village[u].depth + 1;
                village[v].father[0] = u;
                q.push(v);
                visited[v] = true;
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
        for (int i = 19; i >= 0; i--)
        {
            if (village[du].father[i] == village[dv].father[i])
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
        if (endPointOfAC == c && endPointOfBC == c)
        {
            if (vertexInAB == c)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (endPointOfAC == c || endPointOfBC == c)
        {
            return true;
        }
        else
        {
            return false;
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