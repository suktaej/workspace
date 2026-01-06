#include "GraphInput.cpp"
#include <limits>
#include <stack>

bool BellmanFord(const int &start, const int &goal)
{
    const int INF = std::numeric_limits<int>::max();
    std::vector<int> dist(gVertexCount, INF);
    std::vector<int> parent(gVertexCount, -1);

    dist[start] = 0;

    for (int i = 0; i < gVertexCount - 1; ++i)
    {
        bool updated  = false;

        for(const auto& edge : edges)
        {
            if (dist[edge.from] != INF &&
                dist[edge.from] + edge.weight < dist[edge.to])
                {
                    dist[edge.to] = dist[edge.from] + edge.weight;
                    parent[edge.to] = edge.from;
                    updated = true;
                }
        }

        if(!updated)
            break;
    }

    for(const auto& edge : edges)
    {
        if (dist[edge.from] != INF &&
            dist[edge.from] + edge.weight < dist[edge.to])
            return false;
    }

    if (dist[goal] == INF)
        return false; 

    std::stack<int> path;
    for(int v = goal; v != -1; v = parent[v])
        path.push(v);

    while (!path.empty())
    {
        std::cout<<path.top()<<(path.size() > 1 ? "->" : "");
        path.pop();
    }

    return true;
}