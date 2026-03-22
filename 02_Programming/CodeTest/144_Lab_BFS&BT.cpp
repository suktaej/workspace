#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

constexpr int wallCnt = 3;
int n, m;
int grid[8][8] = { 0,};
int testGrid[8][8] = { 0,};
int maxPristine = 0;
int pristineFloor = 0;
int testFloor = 0;
std::vector<std::pair<int,int>> path;
std::vector<std::pair<int,int>> virus;

void bfs();
void solve();

void dfs(std::vector<std::pair<int,int>>::iterator pos, std::vector<std::pair<int,int>>& picked)
{
    if(picked.size() == wallCnt)
    {
        memcpy(testGrid, grid, sizeof(grid));
        for(auto pos : picked)
            testGrid[pos.first][pos.second] = 1;

        testFloor = pristineFloor - 3;
        
        bfs();
        return;
    }

    for (auto it = pos; it != path.end(); ++it)
    {
        picked.push_back(*it);
        dfs(it+1,picked);
        picked.pop_back();
    }
}

void bfs()
{
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};
    std::queue<std::pair<int,int>> q;

    for(auto it : virus)
        q.push({it.first, it.second});

    while(!q.empty())
    {
        std::pair<int,int> cur = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i)
        {
            int ny = cur.first + dy[i];
            int nx = cur.second + dx[i];

            if(nx < 0 || ny < 0 || nx >= m || ny >= n)
                continue;

            if (testGrid[ny][nx] == 0)
            {
                q.push({ny,nx});
                testGrid[ny][nx] = 2;
                --testFloor;
            }
        }
    }

    maxPristine = std::max(maxPristine,testFloor);
}

void solve()
{
    std::cin>>n>>m;
    path.reserve(n * m);
    virus.reserve(n * m);

    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
        {
            std::cin>>grid[i][j];

            if(0 == grid[i][j])
            {
                path.push_back({i,j});
                ++pristineFloor;
            }
            if(2 == grid[i][j])
                virus.push_back({i,j});
        }

    std::sort(path.begin(),path.end());
    std::vector<std::pair<int,int>> picked;
    picked.reserve(wallCnt);

    dfs(path.begin(), picked);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();
    std::cout<<maxPristine;
    return 0;
}