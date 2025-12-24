#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <queue>

std::vector<std::vector<int>> adj;
std::vector<int> dfs;
std::vector<int> bfs;
std::vector<bool> visited;
std::vector<int> nodes;

void DFS(int cur)
{
    visited[cur] = true;

    for(const int& next : adj[cur])
    {
        if(visited[next])
            continue;

        dfs.push_back(next);
        DFS(next);
    }
}

void BFS(int start)
{
    std::queue<int> que;
    que.push(start);
    visited[start] = true;

    while(!que.empty())
    {
        int cur = que.front();
        que.pop();
        bfs.push_back(cur);

        for(const int& next : adj[cur])
        {
            if(visited[next])
                continue;

            visited[next] = true;
            que.push(next);
        }
    }
}

int main()
{
    int vertex, edge, start;
    std::vector<std::pair<int, int>> edges;

    std::cin>>vertex>>edge>>start;
    for (int i = 0; i < edge; ++i)
    {
        int u, v;
        std::cin>>u>>v;
        edges.push_back({u,v});
        nodes.push_back(u);
        nodes.push_back(v);
    }

    std::unordered_map<int, int> idx;

    std::sort(nodes.begin(), nodes.end());
    nodes.erase(std::unique(nodes.begin(), nodes.end()), nodes.end());
    
    int n = nodes.size();
    
    for (int i = 0; i < n; ++i)
        idx[nodes[i]] = i;

    adj.resize(n);
    visited.assign(n,false);

    for (const auto& [u, v] : edges)
    {
        adj[idx[u]].push_back(idx[v]);
        adj[idx[v]].push_back(idx[u]);
    }

    for (std::vector<int>& edges : adj)
        std::sort(edges.begin(),edges.end());

    if(idx.find(start) == idx.end())
        std::cout << start << '\n' << start;
    else
    {
        dfs.push_back(idx[start]);
        DFS(idx[start]);

        visited.assign(n,false);

        BFS(idx[start]);
    }

    for(const int& i : dfs)
        std::cout << nodes[i] << ' ';
    std::cout<<'\n';
    for(const int& i : bfs)
        std::cout << nodes[i] << ' ';
}
