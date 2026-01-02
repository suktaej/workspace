#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>

int gVertexCount;
int gEdgeCount;

struct FEdge
{
    int from;
    int to;
    int weight;

    bool operator<(const FEdge& other) const
    {
        return weight < other.weight;
    }
    
    bool operator>(const FEdge& other) const
    {
        return weight > other.weight;
    }
};

using edgeInfo = std::pair<int, int>; 
std::vector<FEdge> edges;
std::vector<std::vector<edgeInfo>> adj; // {weight, to} : 가중치 기준 정렬 시 pair의 first 기준 정렬

void StdInput()
{
    int u, v, w;
    std::cin >> gVertexCount >> gEdgeCount;
    adj.assign(gVertexCount + 1, std::vector<std::pair<int, int>>());

    for (int i = 0; i < gEdgeCount; ++i)
    {
        std::cin >> u >> v >> w;
        edges.push_back({u, v, w});
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
    }
}

void FileInput()
{
    std::ifstream readFile;
    readFile.open("input.txt");

    if(readFile.is_open())
    {
        int u, v, w;
        readFile >> gVertexCount >> gEdgeCount;
        adj.assign(gVertexCount + 1, std::vector<std::pair<int, int>>());

        for (int i = 0; i < gEdgeCount; ++i)
        {
            readFile >> u >> v >> w;
            edges.push_back({u, v, w});
            adj[u].push_back({w, v});
            adj[v].push_back({w, u});
        }
    }

    // readFile.close();
}

void SortWeight()
{
    int size = adj.size();

    // Prim, Dijkstra의 경우 priority_queue를 사용하므로 중복정렬할 필요없음
    // for (int i = 0; i < size; ++i)
    //     std::sort(adj[i].begin(),adj[i].end(),[](const std::pair<int,int>& a, const std::pair<int,int>& b){
    //         return a.second < b.second;
    //     });

    // Kruskal의 경우 DisjointSet을 활용해야 하므로 정렬이 필요
    std::sort(edges.begin(), edges.end(), [](const FEdge &a, const FEdge &b) {
        return a.weight < b.weight;
    });
}