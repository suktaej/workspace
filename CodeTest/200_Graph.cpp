#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>

constexpr int INF = 1e9;
int n, e;
std::vector<std::vector<std::pair<int,int>>> adj;

void input()
{
    std::cin>>n>>e;
    adj.resize(n);

    for(int i=0;i<e;++i)
    {
        int u, v, w;
        std::cin>>u>>v>>w;
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
    }
}

int dijkstra(const int& src, const int& dest)
{
    std::vector<int> dist(n,INF);
    std::vector<int> prev(n,-1);
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<>> minHeap;

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

        for(const auto& next : adj[curNode])
        {
            auto [nextDist, nextNode] = next;

            if (dist[curNode] != INF &&
                dist[nextNode] > dist[curNode] + nextDist)
                {
                    dist[nextNode] = dist[curNode]+nextDist;
                    prev[nextNode] = curNode;
                    minHeap.push({dist[nextNode], nextNode});
                }
        }
    }

    if(dist[dest]==INF)
        return -1;

    std::stack<int> path;

    for (int i = dest; i != -1; i = prev[i])
        path.push(i);

    return dist[dest];
}

bool prim(const int& src)
{
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<>> minHeap;
    std::vector<bool> visited(n,false);
    
    minHeap.push({0,src});
    int vertexCount = 0;
    int totalWeight = 0;

    while(!minHeap.empty())
    {
        auto [curWeight, curNode] = minHeap.top();
        minHeap.pop();

        if(visited[curNode])
            continue;
        
        visited[curNode] = true;
        ++vertexCount;
        totalWeight += curWeight;

        for(const auto& [nextWeight, nextNode] : adj[curNode])
        {
            if(visited[nextNode])
                continue;
            
            minHeap.push({nextWeight, nextNode});
        }
    }

    return vertexCount == n;
}

struct FDisjointSet
{
    std::vector<int> parents;
    std::vector<int> rank;

    explicit FDisjointSet(int n)
    : parents(n), rank(n,0)
    {
        for (int i = 0; i <= n; ++i)
            parents[i]=i;
    }

    int find(int n)
    {
        if (parents[n] == n)
            return n;

        return parents[n] = find(parents[n]);
    }

    bool unite(int i, int j)
    {
        int rooti = find(i);
        int rootj = find(j);

        if(rooti == rootj)
            return false;

        if(rank[rooti] < rank[rootj])
            std::swap(rooti, rootj);

        parents[rooti] = rootj;

        if(rank[rooti] == rank[rootj])
            ++rank[rooti];

        return true;
    }
};

struct FEdge
{
    int weight;
    int src;
    int dest;

    bool operator<(const FEdge& other) const
    {
        return weight < other.weight;
    }
};

void kruskal()
{
    std::vector<FEdge> edges;
    edges.reserve(n);

    for(int i=0;i<n;++i)
        for(auto e : adj[i])
            if(i < e.second)    // 무방향 그래프일 경우 간선중복 제거
                edges.push_back({e.first, i, e.second});

    std::sort(edges.begin(), edges.end());
    // std::sort(edges.begin(), edges.end(), [](const FEdge& a,const FEdge& b)
    // {
    //     return a.weight < b.weight;
    // });

    FDisjointSet ds(n);
    int edgeCount = 0;
    int totalWeight = 0;

    for(auto edge : edges)
    {
        if(ds.unite(edge.src, edge.dest))
        {
            totalWeight += edge.weight;
            ++edgeCount;

            if(edgeCount == n-1)
                break;
        }
    }
}

std::vector<int> nodeColor;
constexpr int colors = 3;

void coloring()
{
    nodeColor.resize(n,0);
    solve(0);
}

bool isPlace(int node, int color)
{
    for(auto [weight, nextNode]: adj[node])
        if(color == nodeColor[nextNode])
            return false;
    
    return true;
}

bool solve(int node)
{
    if(node == n)
        return true;

    for (int c = 1; c <= colors; ++c)
    {
        if(isPlace(node, c))
        {
            nodeColor[node] = c;

            if(solve(node+1))
                return true;

            nodeColor[node] = 0;
        }
    }

    return false;
}

int main()
{
    input();
    coloring();
    return 0;
}