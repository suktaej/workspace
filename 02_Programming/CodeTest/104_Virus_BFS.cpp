#include <iostream>
#include <vector>
#include <queue>

std::vector<std::vector<int>> g_paths;
int g_Vertex;
int g_Edge;

void input()
{
    std::cin>>g_Vertex>>g_Edge;
    g_paths.assign(g_Vertex + 1,std::vector<int>(0));

    for (int i = 1; i <= g_Edge; ++i)
    {
        int s, d;
        std::cin >> s >> d;
        
        g_paths[s].push_back(d);
        g_paths[d].push_back(s);
    }
}

int bfs(int start)
{
    std::queue<int> q;
    std::vector<bool> visited(g_Vertex + 1, false);
    q.push(start);
    visited[start] = true;
    int infection = 0;

    while(!q.empty())
    {
        int cur = q.front();
        q.pop();

        for(int next : g_paths[cur])
        {
            if(visited[next])
                continue;

            q.push(next);
            visited[next] = true;
            ++infection;
        }
    }

    return infection;
}

int main(void)
{
    input();
    std::cout<<bfs(1);
    return 0;
}