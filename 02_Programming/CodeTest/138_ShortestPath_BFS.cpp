#include <iostream>
#include <vector>
#include <queue>
#include <limits>

void prim()
{
    int V, E, S;
    std::cin>>V>>E>>S;

    std::vector<std::vector<std::pair<int,int>>> edges(V+1,{});
    
    for(int i=0;i<E;++i)
    {
        int u, v, w;
        std::cin>>u>>v>>w;
        edges[u].push_back({w,v});
        edges[v].push_back({w,u});
    }

    constexpr int INF = std::numeric_limits<int>::max();

    std::vector<int> dist(V+1, INF);
    std::vector<bool> visited(V+1,false);
    std::vector<int> parents(V+1,-1);
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<>> pq;

    int totalWeight = 0;
    int connectNodes = 0;
    
    dist[S] = 0;
    pq.push({0,S});

    while(!pq.empty())
    {
        auto [curWeight, curPos] = pq.top();
        pq.pop();

        // lazy 제거
        if(curWeight > dist[curPos])
            continue;

        if(visited[curPos])
            continue;

        visited[curPos] = true;
        totalWeight += curWeight;
        ++connectNodes;

        for(const auto& [nextWeight, nextPos] : edges[curPos])
        {
            if(visited[nextPos])
                continue;

            if(nextWeight < dist[nextPos])
            {
                dist[nextPos] = nextWeight;
                parents[nextPos] = curPos;
                pq.push({nextWeight, nextPos});
            }
        }
    }

    if(connectNodes!=V)
    {
        std::cout<<"INF";
        return;
    }

    std::cout<<"Total Weight:"<<totalWeight<<'\n';

    for (int i = 1; i <= V; ++i)
    {
        if(i==S || parents[i] == -1)
            continue;

        std::cout<<parents[i]<<'-'<<i<<'\n';
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    prim();
    return 0;
}