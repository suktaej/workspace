#include <iostream>
#include <vector>
#include <algorithm>

int bestTrioList(int nodes, int edges, int* from, int* to)
{
    std::vector<std::vector<int>> adj(nodes+1,std::vector<int>());;
    std::vector<int> degree(nodes+1, 0);
    
    for(int i=0;i<edges;++i)
    {
        adj[from[i]].push_back(to[i]);
        adj[to[i]].push_back(from[i]);
        ++degree[from[i]];
        ++degree[to[i]];
    }

    // for(const int& it : degree)
    //     edges += it;
    // edges /= 2;

    int minScore = 1e9;

    for(int i=0;i<edges;++i)
    {
        int u = from[i];
        int v = to[i];

        for (int w = 1; w <= nodes; ++w)
        {
            if (w == u || w == v)
                continue;

            bool uEdge = false;
            bool vEdge = false;

            for(const int& it : adj[u])
                if (it == w)
                    uEdge = true;

            if(uEdge)
                for(const int& it :adj[v])
                    if(it == w)
                        vEdge = true;

            if(vEdge)
            {
                int curScore = (degree[u] - 2) + (degree[v] - 2) + (degree[w] - 2);
                minScore = std::min(minScore, curScore);
            }
        }
    }

    return (minScore == 1e9) ? -1 : minScore;
}

int bestTrioMat(int nodes, int edges, int* from, int* to)
{
    using namespace std;

    vector<vector<bool>> adj(nodes + 1, vector<bool>(nodes + 1, false));
    vector<int> degree(nodes + 1, 0);

    for (int i = 0; i < edges; ++i) 
    {
        adj[from[i]][to[i]] = true;
        adj[to[i]][from[i]] = true;
        ++degree[from[i]];
        ++degree[to[i]];
    }

    int minScore = 1e9;

    for (int i = 0; i < edges; ++i) 
    {
        int u = from[i];
        int v = to[i];

        for (int w = 1; w <= nodes; ++w) 
        {
            if (w == u || w == v) 
                continue;

            if (adj[u][w] && adj[v][w]) 
            {
                int currentScore = (degree[u] - 2) + (degree[v] - 2) + (degree[w] - 2);
                minScore = std::min(minScore, currentScore);
            }
        }
    }

    return (minScore == 1e9) ? -1 : minScore;
}

int main()
{
    int nodes = 6;
    int edges = 6;
    int from[] = {1,2,2,3,4,5};
    int to[] = {2,4,5,5,5,6};

    std::cout << bestTrioMat(nodes, edges, from, to);

    return 0;
}