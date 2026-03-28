/*
    이분 그래프에서 최대매칭 탐색
    BFS로 최단증가경로들의 레벨그래프 구축
    DFS로 여러 개 정점 불포함 증가경로 탐색
    Danic과 유사 (유량이 1)
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

constexpr int INF = std::numeric_limits<int>::max();

class HopcroftKarp
{
private:
    int lVtxCnt, rVtxCnt;
    std::vector<std::vector<int>> adj;
    std::vector<int> lMatch, rMatch, dist;

public:
    HopcroftKarp(int l,int r) 
    : lVtxCnt(l), rVtxCnt(r)
    {
        adj.resize(l+1);
        lMatch.resize(l+1,0);
        rMatch.resize(r+1,0);
        dist.resize(l+1);
    }

    void AddEdge(int u, int v)
    {
        adj[u].push_back(v);
    }

    // 레벨그래프 구축 및 증가 경로 존재여부 확인
    bool BFS()
    {
        std::queue<int> q;

        for (int u = 1; u <= lVtxCnt; ++u)
        {
            if (lMatch[u] == 0)
            {
                dist[u]=0;
                q.push(u);
            }
            else
                dist[u] = INF;
        }
        dist[0] = INF; // 0은 가상의 정점(NIL)

        while(!q.empty())
        {
            int u = q.front();
            q.pop();

            if(dist[u] < dist[0])
            {
                for (int v : adj[u])
                {
                    int nextu = rMatch[v];

                    if(dist[nextu] == INF)
                    {
                        dist[nextu] = dist[u]+1;
                        q.push(nextu);
                    }
                }
            }
        }
        // dist[0] 갱신 시 증가경로 존재
        return dist[0] != INF;
    }

    // 증가경로를 따라 매칭갱신
    bool DFS(int u)
    {
        if(u!=0)
        {
            for (int v : adj[u])
            {
                int nextu = rMatch[v];

                if(dist[nextu] == dist[u]+1)
                {
                    if(DFS(nextu))
                    {
                        rMatch[v] = u;
                        lMatch[u] = v;
                        return true;
                    }
                }
            }

            dist[u] = INF;  //경로없음 처리
            return false;
        }

        return true;
    }

    int MaximumMatching()
    {
        int matching = 0;

        while (BFS())
            for (int u = 1; u <= lVtxCnt; u++)
                if (lMatch[u] == 0 && DFS(u))
                    matching++;

        return matching;
    }
};

int main() 
{
    // 예시: 왼쪽 정점 4개, 오른쪽 정점 4개
    int N = 4, M = 4;
    HopcroftKarp hk(N, M);

    hk.AddEdge(1, 1);
    hk.AddEdge(1, 2);
    hk.AddEdge(2, 2);
    hk.AddEdge(3, 2);
    hk.AddEdge(3, 3);
    hk.AddEdge(4, 3);
    hk.AddEdge(4, 4);

    std::cout << "Maximum matching count: " << hk.MaximumMatching() << std::endl;
    return 0;
}