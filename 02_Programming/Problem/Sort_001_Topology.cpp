#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <queue>
#include <string>

int n;
std::vector<std::vector<int>> adj;
std::vector<int> idxDegree;

void fileInput()
{
    std::fstream in;
    in.open("input.txt");

    if(in.is_open())
    {
        in >> n;

        adj.resize(n + 1);
        idxDegree.resize(n + 1, 0);

        int u, v;

        while (in >> u >> v)
        {
            adj[u].push_back(v);
            ++idxDegree[v];
        }
    }

    in.close();
}

void topology()
{
    std::queue<int> q;
    std::vector<int> res;
    
    for(int i=1; i<= n; ++i)
    {
        if (idxDegree[i] == 0)
            q.push(i);
    }

    while(!q.empty())
    {
        int cur = q.front();
        q.pop();
        res.push_back(cur);

        for(int next : adj[cur])
        {
            --idxDegree[next];

            if(idxDegree[next] == 0)
                q.push(next);
        }
    }

    if (res.size() != n)
        throw std::logic_error("Cycle detected : The graph is not a DAG");

    for(int node : res)
        std::cout << node << " ";
}

struct Node 
{
    std::vector<int> nextNodes;
    int inDegree = 0;
};

std::vector<Node> graph;

void topologySort() 
{
    std::vector<int> result;
    std::queue<int> q;

    for (int i = 1; i <= n; ++i) 
        if (graph[i].inDegree == 0)
            q.push(i);

    while (!q.empty()) 
    {
        int cur = q.front();
        q.pop();
        result.push_back(cur);

        for (int next : graph[cur].nextNodes)
            if (--graph[next].inDegree == 0)
                q.push(next);
    }

    if (result.size() != n)
        throw std::runtime_error("Cycle detected");
}

int main()
{
    fileInput();
    topology();

    return 0;
}