#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cstring>

const int MAX = 101;
int n, m;
std::string maze[MAX];


void bfs()
{
    std::pair<int, int> s = {0, 0};
    int dist[MAX][MAX];
    int dy[] = {1, -1, 0, 0};
    int dx[] = {0, 0, 1, -1};
    std::queue<std::pair<int,int>> q;
    
    memset(dist,-1,sizeof(dist));

    q.push(s);
    dist[s.second][s.first] = 1;

    while(!q.empty())
    {
        int x = q.front().second;
        int y = q.front().first;
        q.pop();

        if(y==n-1 && x == m-1)
        {
            std::cout<<dist[y][x];
            return;
        }

        for(int i=0;i<4;++i)
        {
            int ny = y+dy[i];
            int nx = x+dx[i];

            if (ny < 0 || ny >= n || nx < 0 || nx >= m) 
                continue;

            if (maze[ny][nx] == '0' || dist[ny][nx] != -1) 
                continue;

            dist[ny][nx] = dist[y][x]+1;
            q.push({ny,nx});
        }
    }
}

int main()
{
    std::cin>>n>>m;

    for(int i=0;i<n;++i)
        std::cin>>maze[i];

    bfs();

    return 0;
}