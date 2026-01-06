#include <array>
#include <vector>
#include <queue>
#include <iostream>
#include <climits>

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

int main()
{
    std::cout<<FordFulkerson(0,5);
    return 0;
}