#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <cstring>

int n;
std::vector<std::string> grid;
bool visited[101][101];
int normCount = 0;
int weakCount = 0;

void bfs(int y, int x, char c, bool isNormal)
{
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    std::queue<std::pair<int, int>> q;
    q.push({y, x});
    visited[y][x] = true;

    while (!q.empty())
    {
        auto [cy, cx] = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i)
        {
            int nx = dx[i] + cx;
            int ny = dy[i] + cy;

            if (nx < 0 || ny < 0 || nx >= n || ny >= n)
                continue;

            if(visited[ny][nx])
                continue;

            if(isNormal)
            {
                if (c == grid[ny][nx])
                {
                    visited[ny][nx] = true;
                    q.push({ny,nx});
                }
            }
            else
            {
                if ((c == 'R' || c == 'G') &&
                    ('R' == grid[ny][nx] || 'G' == grid[ny][nx]))
                {
                    visited[ny][nx] = true;
                    q.push({ny,nx});
                }
                else 
                {
                    if (grid[ny][nx] == c) 
                    {
                        visited[ny][nx] = true;
                        q.push({ny,nx});
                    }
                }
            }
        }
    }
}

int main()
{
    std::cin >> n;
    grid.reserve(n);
    memset(visited, false, sizeof(visited));

    for (int i = 0; i < n; ++i)
    {
        std::string temp;
        std::cin >> temp;
        grid.push_back(temp);
    }

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (false == visited[i][j])
            {
                bfs(i, j, grid[i][j], true);
                ++normCount;
            }

    memset(visited, false, sizeof(visited));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (false == visited[i][j])
            {
                bfs(i, j, grid[i][j], false);
                ++weakCount;
            }

    std::cout<<normCount<<' '<<weakCount;

    return 0;
}