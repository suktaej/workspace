#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

struct FEdge
{
    int to;
    int cap;
    int rev;
};

class Dinic
{
private:
    int nodeCount;
    int src, sink;
    std::vector<std::vector<FEdge>> adj;
    std::vector<int> level; // level graph
    std::vector<int> ptr;   // DFS 탐색 효율을 위한 포인터(어디까지 탐색했는지 저장)

public:
    Dinic(int n, int s, int t)
    : nodeCount(n), src(s), sink(t)
    {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

public:
    void AddEdge(int u, int v, int cap);
    bool BFS();
    // pushed : 현재 경로로 보낼 수 있는 최대 예상유량
    int DFS(int v, int pushed);
    int MaxFlow();
};

inline void Dinic::AddEdge(int u, int v, int cap)
{
    adj[u].push_back({v, cap, (int)adj[v].size()});
    adj[v].push_back({u, 0, (int)adj[u].size()-1});
}

inline bool Dinic::BFS()
{
    std::queue<int> que;
    std::fill(level.begin(),level.end(),-1);

    que.push(src);
    level[src] = 0;

    while(!que.empty())
    {
        int cur = que.front();
        que.pop();

        for(const auto& edge : adj[cur])
        {
            if (level[edge.to] != -1)
                continue;

            if (edge.cap > 0)
            {
                level[edge.to] = level[cur] + 1;
                que.push(edge.to);
            }
        }
    }

    return level[sink] != -1;
}

inline int Dinic::DFS(int v, int pushed)
{
    if (pushed == 0)
        return 0;

    if (v == sink)
        return pushed;

    // ptr[v]부터 탐색하여 이미 쓸모없다고 판단된 간선은 다시 보지 않음 (중요 최적화)
    for(int& cid = ptr[v]; cid < adj[v].size(); ++cid)
    {
        auto& edge = adj[v][cid];
        int tr = edge.to;

        //레벨이 1 높은 노드로만 이동
        if (level[v] + 1 != level[tr] ||
            edge.cap == 0)
            continue;

        int tr_pushed = DFS(tr, std::min(pushed, edge.cap));

        if(tr_pushed == 0)
            continue;

        edge.cap -= tr_pushed;
        adj[tr][edge.rev].cap += tr_pushed;

        return tr_pushed;
    }

    return 0;
}

inline int Dinic::MaxFlow()
{
    // 결과값
    int flow = 0;

    // 레벨그래프를 만들 때 까지 반복
    while(BFS())
    {
        // 각 레벨 그래프마다 포인터 초기화
        std::fill(ptr.begin(), ptr.end(), 0);

        while(int pushed = DFS(src, INT_MAX))
            flow += pushed;
    }

    return flow;
}

int main() 
{
    int nodes = 6;
    int source = 0, sink = 5;
    Dinic dinic(nodes, source, sink);

    dinic.AddEdge(0, 1, 16);
    dinic.AddEdge(0, 2, 13);
    dinic.AddEdge(1, 2, 10);
    dinic.AddEdge(1, 3, 12);
    dinic.AddEdge(2, 1, 4);
    dinic.AddEdge(2, 4, 14);
    dinic.AddEdge(3, 2, 9);
    dinic.AddEdge(3, 5, 20);
    dinic.AddEdge(4, 3, 7);
    dinic.AddEdge(4, 5, 4);

    std::cout << "Max Flow (Dinic): " << dinic.MaxFlow() << std::endl;

    return 0;
}