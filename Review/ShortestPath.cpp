#include <array>
#include <vector>
#include <queue>
#include <stack>
#include <iostream>

constexpr int GRIDSIZE = 6;
constexpr int DIRSIZE = 4;
std::array<std::pair<int, int>,4> dir = {{{0, 1}, {0, -1}, {1, 0}, {-1, 0}}};
std::array<std::array<int,GRIDSIZE>,GRIDSIZE> grid = 
{{
    {0, 0, 1, 0, 0, 0},
    {1, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 0}
}};

struct Fdir
{
    int x, y;
};

bool BFS(std::pair<int,int> start, std::pair<int,int> goal)
{
    std::queue<std::pair<int,int>> q;
    std::vector<std::vector<bool>> visited(GRIDSIZE, std::vector<bool>(GRIDSIZE,false));
    constexpr std::pair<int,int> INIT = {-1,-1};
    std::vector<std::vector<std::pair<int, int>>> parent(GRIDSIZE, std::vector<std::pair<int, int>>(GRIDSIZE, INIT));
    int dist = 0;

    q.push(start);
    visited[start.second][start.first] = true;

    while(!q.empty())
    {
        int qSize = q.size();

        while(qSize--)
        {
            auto [curY, curX] = q.front();
            q.pop();

            if (curY == goal.second && curX == goal.first)
            {
                std::stack<std::pair<int, int>> route;
                std::pair<int, int> temp = goal;

                while (temp != INIT)
                {
                    route.push(temp);
                    temp = parent[temp.second][temp.first];
                }

                while (!route.empty())
                {
                    std::cout << "(" << route.top().first << "," << route.top().second << ")" << (route.size() > 1 ? " -> " : "");
                    route.pop();
                }

                std::cout << "\nPath distance: " << dist << "\n";

                return true;
            }

            for (int i = 0; i < DIRSIZE; ++i)
            {
                auto [dirY, dirX] = dir[i];
                int nextX = curX + dirX;
                int nextY = curY + dirY;

                if (nextX < 0 || nextX >= GRIDSIZE || nextY < 0 || nextY >= GRIDSIZE)
                    continue;

                if (grid[nextY][nextX] == 1)
                    continue;

                if (visited[nextY][nextX])
                    continue;

                visited[nextY][nextX] = true;
                parent[nextY][nextX] = {curX, curY};
                q.push({nextY, nextX});
            }
        }
        ++dist;
    }

    return false;
}

int main()
{
    std::pair<int,int> start, goal; //(x,y)
    start = {0,0};
    goal = {5,5};
    BFS(start,goal);

    return 0;
}