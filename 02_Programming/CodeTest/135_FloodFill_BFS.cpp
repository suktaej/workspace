#include <iostream>
#include <queue>

constexpr int gridSize = 10;
int grid[gridSize][gridSize] = {0,};
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};

void bfs(int i, int j)
{
    if(grid[i][j]!=0)
        return;

    std::queue<std::pair<int,int>> q;
   
    q.push({i,j});
    grid[i][j] = 1;

    while(!q.empty())
    {
        const auto& [cy, cx] = q.front();
        q.pop();
        
        for(int i = 0;i<4;++i)
        {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (nx < 0 || ny < 0 || nx >= gridSize || ny >= gridSize)
                continue;

            if (grid[ny][nx] == 0)
            {
                grid[ny][nx] = 1;
                q.push({ny,nx});
            }
        }
    }
}

int main()
{
    bfs(0, 0);
    return 0;
}