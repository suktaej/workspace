#include <iostream>
#include <vector>
#include <queue>

const std::vector<std::vector<int>> gAdj;
int gNodeCount;

bool IsBipartiteBFS()
{
    std::vector<int> color(gNodeCount+1, -1);

    for(int i=1;i<=gNodeCount;++i)
    {
        if(color[i] == -1)
        {
            std::queue<int> q;
            q.push(i);
            color[i] = 0;

            while(!q.empty())
            {
                int u = q.front();
                q.pop();

                for(int v : gAdj[u])
                {
                    if(color[v] == -1)
                    {
                        // 반대색상
                        color[v] = 1 - color[u];
                        q.push(v);
                    }
                    else if(color[v] == color[u])
                        return false;
                }
            }
        }
    }

    return true;
}

bool DFS(int u, int c, std::vector<int>& color)
{
    // 현재 노드 색칠
    color[u] = c;

    for(int v : gAdj[u])
    {
        if(color[v] == -1)
        {
            // 방문하지 않은 인접 노드를 반대로 칠하고 재귀
            if(!DFS(v,1-c,color))
                return false;
        }
        else if(color[v] == color[u])
            return false;
    }

    return true;
}

bool IsBipartiteDFS()
{
    std::vector<int> color(gNodeCount+1, -1);

    for (int i = 1; i <= gNodeCount; ++i)
        if(color[i] == -1)
            if(!DFS(i,0,color))
                return false;

    return true;
}

int main() 
{
    int n = 4, e = 4;
    std::vector<std::vector<int>> adj(n + 1);

    // 예시 1: 이분 그래프인 경우 (사각형 모양)
    // 1-2, 2-3, 3-4, 4-1
    adj[1].push_back(2); adj[2].push_back(1);
    adj[2].push_back(3); adj[3].push_back(2);
    adj[3].push_back(4); adj[4].push_back(3);
    adj[4].push_back(1); adj[1].push_back(4);

    std::cout << "BFS 결과: " << (IsBipartiteBFS() ? "이분 그래프입니다." : "이분 그래프가 아닙니다.") << std::endl;
    std::cout << "DFS 결과: " << (IsBipartiteDFS() ? "이분 그래프입니다." : "이분 그래프가 아닙니다.") << std::endl;

    // 예시 2: 이분 그래프가 아닌 경우 (삼각형 포함)
    // 1-2, 2-3, 3-1 추가
    adj[1].push_back(3); adj[3].push_back(1);
    
    std::cout << "삼각형 추가 후 결과: " << (IsBipartiteBFS() ? "이분 그래프입니다." : "이분 그래프가 아닙니다.") << std::endl;

    return 0;
}