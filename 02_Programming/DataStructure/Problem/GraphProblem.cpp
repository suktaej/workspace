#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <queue>
#include <limits>
#include <numeric>
#include <algorithm>

void GraphTest();

struct Edge
{
    int to;
    int weight;

    Edge() : to(std::numeric_limits<int>::max()), weight(0)
    {
    }

    Edge(const int& to, const int& w) : to(to), weight(w)
    {
    }
};

struct DisjointSet
{
    std::vector<int> parent;    // Set의 represent index
    std::vector<int> rank;      // Set의 depth

    explicit DisjointSet(int size)
        : parent(size), rank(size, 0)
    {
        std::iota(parent.begin(), parent.end(), 0); // 0부터 시작해서 값을 초기화
        // 각 element는 자기 자신을 대표로 독립된 집합을 보유
    }

    int find(const int& element)
    {
        if (parent[element] != element) // parent[element] == element 라면 자신이 대표
            parent[element] = find(parent[element]); // path compression

        return parent[element];
    }

    void unite(int f, int s)
    {
        f = find(f);
        s = find(s);

        if (f == s) // 이미 동일한 set
            return;

        if (rank[f] < rank[s])
            std::swap(f, s);

        parent[s] = f;

        if (rank[f] == rank[s])
            rank[f]++;
    }
};

class Graph
{
private:
    std::vector<std::list<Edge>> mAdjList;
    int mVertexCount;

public:
    Graph()
        : mVertexCount(0)
    {
    }

    Graph(const int& vertexCount)
        : mAdjList(vertexCount), mVertexCount(vertexCount)
    {
    }

public:
    void addVertex(const int& vertex)
    {
        for (int i = 0; i < vertex; ++i)
        {
            mAdjList.emplace_back();
            ++mVertexCount;
        }
    }

    void addVertex()
    {
        mAdjList.emplace_back();
        mVertexCount++;
    }

    void addEdge(const int& src, const int& dest, const int& weight)
    {
        if (src >= mVertexCount || dest >= mVertexCount)
            throw std::out_of_range("Vertex index out of range");

        mAdjList[src].emplace_back(dest, weight);
    }

    bool removeEdge(const int& src, const int& dest)
    {
        if (src >= mVertexCount || dest >= mVertexCount)
            throw std::out_of_range("Vertex index out of range");

        for (auto it = mAdjList[src].begin(); it != mAdjList[src].end(); ++it)
        {
            if (it->to == dest)
            {
                mAdjList[src].erase(it);
                return true;
            }
        }
        return false;
    }

    void removeVertex(const int& vertex)
    {
        if (vertex >= mVertexCount)
            throw std::out_of_range("Vertex index out of range");

        for (auto& adj : mAdjList)
        {
            auto it = adj.begin();

            while (it != adj.end())
            {
                if (it->to == vertex)
                    it = adj.erase(it);
                else
                    ++it;
            }
        }

        mAdjList.erase(mAdjList.begin() + vertex);

        mVertexCount--;
    }

    void DFS_Stack(const int& start)
    {
        std::vector<bool> visited(mVertexCount, false);
        std::stack<int> dfsStack;

        if (start >= mVertexCount)
            throw std::out_of_range("Vertex index out of range");

        dfsStack.push(start);

        while (!dfsStack.empty())
        {
            int vertex = dfsStack.top();
            dfsStack.pop();

            if (visited[vertex] == false)
            {
                visited[vertex] = true;
                std::cout << vertex << " ";

                for (auto it = mAdjList[vertex].rbegin(); it != mAdjList[vertex].rend(); ++it)
                {
                    int nextVertex = it->to;

                    if (false == visited[nextVertex])
                        dfsStack.push(nextVertex);
                }
            }
        }
    }

    void DFS_Recursive(const int& start)
    {
        std::vector<bool> visited(mVertexCount, false);
        RecursiveInternal(start, visited);
    }

    void RecursiveInternal(const int& vertex, std::vector<bool>& visited)
    {
        if (vertex >= mVertexCount)
            throw std::out_of_range("Vertex index out of range");

        visited[vertex] = true;
        std::cout << vertex << " ";

        for (auto it = mAdjList[vertex].begin(); it != mAdjList[vertex].end(); ++it)
        {
            int nextVertex = it->to;

            if (visited[nextVertex] == false)
                RecursiveInternal(it->to, visited);
        }
    }

    void BFS(const int& start)
    {
        std::vector<bool> visited(mVertexCount, false);
        std::queue<int> bfsQueue;

        bfsQueue.push(start);
        visited[start] = true;

        while (!bfsQueue.empty())
        {
            int vertex = bfsQueue.front();
            bfsQueue.pop();

            std::cout << vertex << " ";

            for (auto it = mAdjList[vertex].begin(); it != mAdjList[vertex].end(); ++it)
            {
                int nextVertex = it->to;
                if (visited[nextVertex] == false)
                {
                    bfsQueue.push(nextVertex);
                    visited[nextVertex] = true;
                }
            }
        }
    }

    void Prim(const int& start)
    {
        using edgeinfo = std::pair<int, int>; // weight, dest
        std::priority_queue<edgeinfo, std::vector<edgeinfo>, std::greater<>> minHeap; // type, container, priority   
        std::vector<bool> visited(mVertexCount, false);

        if (start >= mVertexCount)
            throw std::out_of_range("Vertex index out of range");

        visited[start] = true;

        for (const auto& it : mAdjList[start])
            minHeap.push({it.weight, it.to});

        while (!minHeap.empty())
        {
            // auto [weight, dest] = minHeap.top();    // C++ 17
            int weight = minHeap.top().first;
            int dest = minHeap.top().second;
            minHeap.pop();

            if (visited[dest] == false)
            {
                visited[dest] = true;
                std::cout << dest << " (weight: " << weight << ")\n";

                for (const auto& it : mAdjList[dest])
                {
                    if (false == visited[it.to])
                        minHeap.push({it.weight, it.to});
                }
            }
        }
    }

    void Kruskal()
    {
        using Edgeinfo = std::pair<int, std::pair<int, int>>;   // weight, {src, dest}
        std::vector<Edgeinfo> edges;

        // 모든 edge 수집
        for (int src = 0; src < mVertexCount; ++src)
        {
            for (const auto& it : mAdjList[src])
                edges.push_back({it.weight, {src, it.to}});
        }

        // 가중치 기준 정렬
        std::sort(edges.begin(), edges.end());

        // 서로소집합 생성
        DisjointSet ds(mVertexCount);
        int edgeCount = 0;
        int totalWeight = 0;

        for (const auto& it : edges)
        {
            int src = it.second.first;
            int dest = it.second.second;

            int rootSrc = ds.find(src);
            int rootDest = ds.find(dest);

            // 같은 집합이 아닐 경우
            if (rootSrc != rootDest)
            {
                ds.unite(rootSrc, rootDest);
                std::cout << "(" << src << " -> " << dest << ") weight: " << it.first << "\n";
                totalWeight += it.first;
                ++edgeCount;
            }

            // 종료조건(간선의 수가 정점의 수보다 1만큼 작을 경우)
            if (edgeCount == mVertexCount -1)
                break;
        }
    }
};

int main(int argc, char* argv[])
{
    GraphTest();
    return 0;
}

void GraphTest()
{
    Graph* grp = new Graph(5);

    grp->addEdge(0, 1, 10);
    grp->addEdge(0, 2, 20);
    grp->addEdge(0, 3, 50);
    grp->addEdge(1, 2, 60);
    grp->addEdge(1, 4, 20);
    grp->addEdge(2, 3, 20);
    grp->addEdge(2, 4, 10);
    grp->addEdge(3, 4, 50);
    grp->addEdge(4, 1, 20);
    grp->addEdge(3, 0, 60);

    grp->DFS_Stack(1);
    std::cout << std::endl;
    grp->DFS_Recursive(0);
    std::cout << std::endl;
    grp->BFS(1);
    std::cout << std::endl;
    grp->Prim(0);
    std::cout << std::endl;
    grp->Kruskal();
}
