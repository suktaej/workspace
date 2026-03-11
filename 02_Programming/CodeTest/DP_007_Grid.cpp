#include <array>
#include <vector>
#include <iostream>

constexpr int size = 6;
const std::array<std::pair<int, int>, 2> OBSTACLE = {{{2, 2}, {5, 1}}};
const std::array<std::pair<int, int>, 4> DIR = {{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}};

bool IsObstacle(int x, int y)
{
    for(auto& [ox, oy] : OBSTACLE)
        if(x == ox && y == oy)
            return true;

    return false;
}

int DP()
{
    std::array<std::array<int,size>,size> dp = {};
    dp[0][0] = 1;

    for (int y = 0; y < size; ++y)
    {
        for (int x = 0; x < size; ++x)
        {
            if (0 == x && 0 == y)
                continue;

            if (IsObstacle(x, y))
            {
                dp[x][y] = 0;
                continue;
            }

            int left = (x > 0) ? dp[x - 1][y] : 0;
            int down = (y > 0) ? dp[x][y - 1] : 0;

            dp[y][x] = left + down;
        }
    }

    return dp[size-1][size-1];
}

int DFS(int x, int y, std::array<std::array<bool, size>, size>& visited)
{
    if (x == size - 1 && y == size - 1)
        return 1;
    
    int count = 0;

    for (auto [dx, dy] : DIR)
    {
        int nx = x + dx;
        int ny = y + dy;
        
        if (nx < 0 || ny < 0 || nx >= size || ny >= size)
            continue;

        if(visited[ny][nx])
            continue;

        if (IsObstacle(nx, ny))
            continue;
        
        visited[ny][nx] = true;
        count += DFS(nx, ny, visited);
        visited[ny][nx] = false;
    }

    return count;
}

int main()
{
    std::array<std::array<bool, size>, size> visited{};
    visited[0][0] = true;

    std::cout << DFS(0, 0, visited) << std::endl;
    std::cout<<DP();
    
    return 0;
}