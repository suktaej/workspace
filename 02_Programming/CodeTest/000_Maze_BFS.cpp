#include <queue>
#include <array>
#include <iostream>

constexpr int gridSize = 3;
constexpr int dir = 4;

const std::array<std::array<int, gridSize>, gridSize> grid = {{{0, 0, 1},
                                                               {1, 0, 1},
                                                               {0, 0, 0}}};

const std::array<std::pair<int, int>, dir> dirPos = {{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}};
const std::pair<int, int> goal = {gridSize - 1, gridSize - 1};

int BFS()
{
    std::queue<std::pair<int, int>> que;
    std::array<std::array<bool, gridSize>, gridSize> visited{};

    que.push({0, 0});
    visited[0][0] = true;

    int dist = 0;

    while (!que.empty())
    {
        int qSize = que.size();

        while(qSize--)
        {
            std::pair<int, int> pos = que.front();
            int xPos = pos.second;
            int yPos = pos.first;
            que.pop();
            
            if (yPos == goal.first && xPos == goal.second)
                return dist;

            for (int i = 0; i < dir; ++i)
            {
                int nx = xPos + dirPos[i].second;
                int ny = yPos + dirPos[i].first;

                if (ny < 0 || nx < 0 || ny >= gridSize || nx >= gridSize)
                    continue;

                if (visited[ny][nx])
                    continue;

                if (grid[ny][nx] == 1)
                    continue;

                visited[ny][nx] = true;
                que.push({ny, nx});
            }
        }
        ++dist;
    }

    return -1;
}

int main(void)
{
    std::cout<<BFS();
    return 0;
}
