#include <iostream>
#include <queue>
#include <vector>

constexpr int INF = 1e9;
int n, e;
std::vector<std::vector<std::pair<int,int>>> gNode;

void input()
{
    std::cin>>n>>e;
    gNode.resize(n);

    for(int i=0;i<e;++i)
    {
        int u, v, w;
        std::cin>>u>>v>>w;
        gNode[u].push_back({w, v});
        gNode[v].push_back({w, u});
    }
}

int dfs(int src, int dest)
{
    std::vector<int> dist(n,INF);
    std::vector<int> parent(n);
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<>> minHeap;

    for(int i=0;i<n;++i)
        parent[i] = i;

    dist[src] = 0;
    minHeap.push({dist[src],src});

    while(!minHeap.empty())
    {
        auto [curDist, curNode] = minHeap.top();
        minHeap.pop();

        if(curNode == dest)
            break;
        
        // 중복된 vertex가 삽입가능하므로
        // outdate entry skip
        if(dist[curNode] < curDist)
            continue;

        for(const auto& next : gNode[curNode])
        {
            auto [nextDist, nextNode] = next;
        }
    }
}

int main()
{
    input();
    return 0;
}