#include <array>
#include <vector>
#include <queue>
#include <iostream>
#include <climits>

// Edmonds-Karp : BFS 방식 fordFulkerson
// adjacent matrix
constexpr int NODE = 6;
std::array<std::array<int, NODE>, NODE> gGraph =
    {{{0, 16, 13, 0, 0, 0},
      {0, 0, 10, 12, 0, 0},
      {0, 4, 0, 0, 14, 0},
      {0, 0, 9, 0, 0, 20},
      {0, 0, 0, 7, 0, 4},
      {0, 0, 0, 0, 0, 0}}};
    

bool BFS(const std::array<std::array<int, 6>, 6> &graph, std::vector<int> &parent, int start, int goal)
{
    std::vector<bool> visited(NODE,false);
    std::queue<int> que;

    que.push(start);
    visited[start] = true;

    while(!que.empty())
    {
        int cur = que.front();
        que.pop();

        for (int next = 0; next < NODE; ++next)
        {
            if(visited[next])
                continue;

            if(graph[cur][next] > 0)
            {
                parent[next] = cur;

                if(goal == next)
                    return true;

                que.push(next);
                visited[next] = true;
            }
        }
    }

    return false;
}

int FordFulkerson(int start, int goal)
{
    // 잔여 그래프 생성(Residual Graph)
    // 초기값은 원본과 동일
    std::array<std::array<int,NODE>,NODE> rGraph = gGraph;
    std::vector<int> parent(NODE, -1);
    // 결과값
    int maxFlow = 0;

    // BFS로 증가경로가 존재할 때 까지 반복
    while (BFS(rGraph, parent, start, goal))
    {
        // 최소유량 탐색
        int pathFlow = INT_MAX;

        for (int trace = goal; start != trace; trace = parent[trace])
        {
            int src = parent[trace];
            pathFlow = std::min(pathFlow, rGraph[src][trace]);
        }

        // 잔여 그래프 갱신(순방향 감소, 역방향 추가)
        for (int trace = goal; start != trace; trace = parent[trace])
        {
            int src = parent[trace];
            rGraph[src][trace] -= pathFlow;
            rGraph[trace][src] += pathFlow;
        }

        std::cout<<"Minimum flow in this path: "<<pathFlow<<'\n';
        maxFlow += pathFlow;
    }

    return maxFlow;
}

// ajdacent list 사용 시
struct FEdge
{
    int to;         // 목적지
    int capacity;   // 잔여용량
    int rev;        // 상대방 node list에서 역방향 edge index
};

class MaxFlow
{
private:
    int nodeCount;
    std::vector<std::vector<FEdge>> adj;
    std::vector<int> level;     // BFS경로 확인용 (부모노드와 간선 인덱스 저장용)

    struct Parent
    {
        int node;
        int edgeIdx;
    };

public:
    MaxFlow(int n) : nodeCount(n) { adj.resize(n); }
    
public:
    void AddEdge(int u, int v, int cap);
    int GetFlow(int s, int t);
};

inline void MaxFlow::AddEdge(int u, int v, int cap)
{
    // 순방향 간선: u -> v, 용량 cap, 역방향은 adj[v]의 마지막 원소
    FEdge a = {v, cap, (int)adj[v].size()};
    // 역방향 간선: v -> u, 용량 0, 역방향은 adj[u]의 마지막 원소
    FEdge b = {u, 0, (int)adj[u].size()};

    adj[u].push_back(a);
    adj[v].push_back(b);
}

inline int MaxFlow::GetFlow(int s, int t)
{
    int totalFlow = 0;

    while(true)
    {
        // parent[v] = {u, idx} -> v의 부모는 u이고, u의 리스트에서 idx번째 간선을 타고 옴
        std::vector<Parent> parent(nodeCount, {-1, -1});
        std::queue<int> que;
        
        que.push(s);

        while (!que.empty() &&
               parent[t].node == -1)
        {
            int cur = que.front();
            que.pop();

            for (int i = 0; i < adj[cur].size(); ++i)
            {
                FEdge &edge = adj[cur][i];

                if (parent[edge.to].node == -1 &&
                    edge.to != s &&
                    edge.capacity > 0)
                {
                    parent[edge.to] = {cur, i};
                    que.push(edge.to);
                }
            }
        }
        
        // 더 이상 경로가 없다면 종료
        if (parent[t].node == -1)
            break;

        // 경로 상 최소유량 탐색
        int pathFlow = INT_MAX;
        for(int v = t; v != s; v = parent[v].node)
        {
            int u = parent[v].node;
            int idx = parent[v].edgeIdx;
            pathFlow = std::min(pathFlow, adj[u][idx].capacity);
        }

        // 잔여용량 갱신
        for(int v = t; v != s; v = parent[v].node)
        {
            int u = parent[v].node;
            int idx = parent[v].edgeIdx;
            int revIdx = adj[u][idx].rev;

            adj[u][idx].capacity -= pathFlow;
            adj[v][revIdx].capacity += pathFlow;
        }

        totalFlow += pathFlow;
    }

    return totalFlow;
}

int main()
{
    std::cout<<FordFulkerson(0,5);
    return 0;
}