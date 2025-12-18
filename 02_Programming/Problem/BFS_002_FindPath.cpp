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

int ShortestLength()
{
    int size = path.size();
    std::queue<int> que;
    std::vector<int> dist(size,INF);

    que.push(0);
    dist[0] = 0;

    while(!que.empty())
    {
        int cur = que.front();
        que.pop();

        for (int &i : path[cur])
        {
            if(dist[i] > dist[cur]+1)
            {
                dist[i] = dist[cur]+1;
                que.push(i);
            }
        }
    }
    
    return dist[size-1];
}

void RestorePaths(
    int cur,
    const std::vector<std::vector<int>>& parents,
    std::vector<int>& pathStack,
    std::vector<std::vector<int>>& allPaths)
{
    pathStack.push_back(cur);

    if (cur == 0)
    {
        std::vector<int> path = pathStack;
        std::reverse(path.begin(), path.end());
        allPaths.push_back(path);
    }
    else
    {
        for (int p : parents[cur])
            RestorePaths(p, parents, pathStack, allPaths);
    }

    pathStack.pop_back();
}

void ShortestPath()
{
    int size = path.size();
    std::queue<int> que;
    std::vector<int> dist(size,INF);
    std::vector<int> cnt(size,0);
    // std::vector<int> parent(size,-1);
    std::vector<std::vector<int>> parents(size);

    que.push(0);
    dist[0] = 0;
    cnt[0] = 1;
    // parent[0] = -1;

    while(!que.empty())
    {
        int cur = que.front();
        que.pop();

        for(int& i : path[cur])
        {
            if (dist[i] > dist[cur] + 1)
            {
                dist[i] = dist[cur]+1;
                que.push(i);

                // parent[i] = cur;
                parents[i].clear();
                parents[i].push_back(cur);
                cnt[i] = cnt[cur];
            }
            else if (dist[i] == dist[cur] + 1)
            {
                cnt[i] += cnt[cur];
                parents[i].push_back(cur);
            }
        }
    }

    /*
    if (dist[size - 1] != INF)
    {
        int dest = size - 1;
        std::vector<int> restore;

        while (dest != -1)
        {
            restore.push_back(dest);
            dest = parent[dest];
        }

        std::reverse(restore.begin(), restore.end());
        std::cout<<"Shortest Path: ";
        for(const int& i : restore)
            std::cout<<i<<" ";
        std::cout<<"\n";
    }
    */

   std::vector<std::vector<int>> allPaths;
   std::vector<int> pathStack;
   RestorePaths(size - 1, parents, pathStack, allPaths);

   std::cout << "All shortest paths:\n";
    for (const auto& p : allPaths)
    {
        for (int v : p)
            std::cout << v << " ";
        std::cout << "\n";
    }

   std::cout << "Number of shortest path: " << cnt[size - 1] << "\n";
   std::cout << "Minimum number of move: " << dist[size - 1] << "\n";
}


int main()
{
    ShortestPath();
    return 0;
}