#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

std::string gMap[25];
int n;

int bfs(int y, int x)
{
    int cnt = 0;
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    std::queue<std::pair<int, int>> q;
    q.push({y, x});
    gMap[y][x] = '0';

    while (!q.empty())
    {
        auto [cy, cx] = q.front();
        q.pop();
        ++cnt;

        for (int k = 0; k < 4; ++k)
        {
            int ny = cy + dy[k];
            int nx = cx + dx[k];

            if (ny < 0 || nx < 0 || ny >= n || nx >= n)
                continue;

            if (gMap[ny][nx] == '1')
            {
                q.push({ny, nx});
                gMap[ny][nx] = '0';
            }
        }
    }
    
    return cnt;
}

int main()
{
    std::cin >> n;

    for (int i = 0; i < n; ++i)
        std::cin >> gMap[i];

    std::vector<int> estate;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (gMap[i][j] == '1')
                estate.push_back(bfs(i, j));

    std::sort(estate.begin(), estate.end());

    std::cout << estate.size() << "\n";
    for (int i : estate)
        std::cout << i << '\n';

    return 0;
}