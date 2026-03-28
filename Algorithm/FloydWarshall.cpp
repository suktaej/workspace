#include "GraphInput.cpp"
#include <limits>

constexpr int INF = std::numeric_limits<int>::max() / 2;

void FloydWarshall()
{
    std::vector<std::vector<int>> dist(gVertexCount, std::vector<int>(gVertexCount + 1, INF));

    for (int i = 0; i < gVertexCount; ++i)
        dist[i][i] = 0;

    for (int i = 0; i < gVertexCount; ++i)
        for (const auto &edge : edges)
            dist[i][edge.to] = edge.weight;

    for (int k = 0; k < gVertexCount; ++k)
        for (int i = 0; i < gVertexCount; ++i)
            for (int j = 0; j < gVertexCount; ++j)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    Output(dist);
}

void Output(std::vector<std::vector<int>> dist)
{
    for (int i = 0; i < gVertexCount; ++i)
    {
        for (int j = 0; j < gVertexCount; ++j)
        {
            if(dist[i][j]== INF)
                std::cout <<"INF";
            else
                std::cout<<dist[i][j]<<" ";
        }
        std::cout<<"\n";
    }
}