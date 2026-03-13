#include <iostream>
#include <queue>
#include <vector>

int n, m;
std::vector<std::vector<int>> graph;
std::vector<bool> visited;

struct disjointSet
{
    std::vector<int> parents;
    std::vector<int> rank;
    int numSet;

    disjointSet(int n)
    : parents(n+1), rank(n+1), numSet(n)
    {
        for(int i=0;i<=n;++i)
            parents[i]= i;
    }

    int find(int i)
    {
        if(parents[i]==i)
            return i;

        return parents[i] = find(parents[i]);
    }

    bool unite(int i,int j)
    {
        int rooti = find(i);
        int rootj = find(j);

        if(rooti==rootj)
            return false;

        if(rank[rooti] < rank[rootj])
            std::swap(rooti, rootj);

        parents[rootj] = rooti;

        if(rank[rooti]==rank[rootj])
            ++rank[rooti];
        
        --numSet;
        return true;
    }

    int Components()
    {
        // int cnt = 0;

        // for(int i=1;i<=n;++i)
        //     if(parents[i]==i)
        //         ++cnt;

        // return cnt;
        return numSet;
    }
};

void bfs(int src)
{
    std::queue<int> q;

    q.push(src);
    visited[src] = true;

    while(!q.empty())
    {
        int cur = q.front();
        q.pop();

        for(const int& node : graph[cur])
        {
            if(visited[node])
            {
                continue;
            }

            q.push(node);
            visited[node] = true;
        }
    }
}

void dfs(int node)
{
    visited[node] = true;
    
    for(const int& next : graph[node])
        if(!visited[next])
            dfs(next);
}

void ds()
{
    struct disjointSet s(n);

    for(int i=1;i<=n;++i)
        for(const auto& j : graph[i])
            s.unite(i,j);

    std::cout<<s.Components();
}

/*
int main()
{
    std::cin>>n>>m;
    graph.resize(n+1);
    visited.resize(n+1,false);

    for(int i=0;i<m;++i)
    {
        int u, v;
        std::cin>>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    ds();

    // int cnt = 0;

    // for(int i=1;i<=n;++i)
    // {
    //     if (!visited[i])
    //     {
    //         ++cnt;
    //         // bfs(i);
    //         // dfs(i);
    //     }
    // }

    // std::cout<<cnt;

    return 0;
}

*/

int main()
{
    int n;
    int blocks[] = {1,2,2};
    std::cin>>n;

    std::vector<int> dp(n+1,0);
    dp[0]=1;
    
    for(int i =1;i<=n;++i)
        for(const int& block : blocks)
            if(i-block >= 0)
                dp[i] += dp[i-block];
    
    std::cout << dp[n];
    
    return 0;
}