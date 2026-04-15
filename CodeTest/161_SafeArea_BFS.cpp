#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

int n;
std::vector<std::vector<int>> grid;
std::vector<std::vector<bool>> visited;
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

void bfs(int y, int x, int height)
{
    std::queue<std::pair<int,int>> q;
    q.push({y,x});
    visited[y][x] = true;

    while(!q.empty())
    {
        auto [cy, cx] = q.front();
        q.pop();

        for(int i=0;i<4;++i)
        {
            int nx = dx[i]+cx;
            int ny = dy[i]+cy;

            if (nx < 0 || ny < 0 || nx >= n || ny >= n)
                continue;

            if(grid[ny][nx]<=height)
                continue;

            if(visited[ny][nx])
                continue;

            q.push({ny,nx});
            visited[ny][nx] = true;
        }
    }
}

void dfs(int y, int x, int h) 
{
    visited[y][x] = true;

    for (int i = 0; i < 4; ++i) 
    {
        int ny = y + dy[i];
        int nx = x + dx[i];

        if (ny >= 0 && ny < n && nx >= 0 && nx < n)
            if (!visited[ny][nx] && grid[ny][nx] > h)
                dfs(ny, nx, h);
    }
}

int main()
{
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    std::cin>>n;
    grid.assign(n,std::vector<int>(n,0));
    visited.assign(n, std::vector<bool>(n, false));

    int highest = 0;
    int lowest = 101;

    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
        {
            std::cin>>grid[i][j];

            if (grid[i][j] < lowest) 
                lowest = grid[i][j];
            if (grid[i][j] > highest) 
                highest = grid[i][j];
        }

    int res = 1;

    for (int k = lowest; k <= highest; ++k)
    {
        int areaCount = 0;

        for(int i=0;i<n;++i)
            std::fill(visited[i].begin(),visited[i].end(),false);

        for(int i=0;i<n;++i)
        {
            for(int j=0;j<n;++j)
            {
                if(grid[i][j]<=k)
                    continue;

                if(visited[i][j])
                    continue;

                bfs(i,j,k);
                ++areaCount;
            }
        }

        res = std::max(areaCount,res);
    }

    std::cout<<res;

    return 0;
}