#include <iostream>
#include <vector>
#include <queue>
#include <limits>

constexpr int INF = std::numeric_limits<int>::max();

std::vector<std::vector<int>> path = {
    {1,2},
    {2,4},
    {3},
    {4,5},
    {5},
    {}
};

int BFS()
{
    int size = path.size();

    std::vector<int> dist(size, INF);
    std::vector<int> count(size, 0);
    std::queue<int> q;

    dist[0] = 0;
    count[0] = 1;
    q.push(0);

    while(!q.empty())
    {
        int u = q.front();
        q.pop();

        for(int v : path[u])
        {
            if (dist[v] > dist[u] + 1)  // 더 짧은 경로 발견
            {
                dist[v] = dist[u] + 1;
                count[v] = count[u];
                q.push(v);
            }
            else if (dist[v] == dist[u] + 1) // 동일한 최단거리 경로 발견
                count[v] += count[u];
        }
    }

    std::cout << "Minimum number of moves:" << dist[5] << "\n";
    std::cout << "Number of path: " << count[5] << "\n";

    return dist[5];
}

int main()
{
    return 0;
}