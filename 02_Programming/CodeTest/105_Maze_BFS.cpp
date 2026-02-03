#include <iostream>
#include <vector>
#include <string>
#include <queue>

struct FPos
{
    int x, y;

    FPos operator+(const FPos& other) const
    {
        FPos res;
        res.x = x + other.x;
        res.y = y + other.y;

        return res;
    }
};

void input(std::vector<std::vector<int>>& maze, int& row, int& col)
{
    std::cin >> row >> col;
    maze.assign(row + 1, std::vector<int>(col + 1, 0));

    for (int i = 1; i <= row; ++i)
    {
        std::string str;
        std::cin >> str;

        for (int j = 1; j <= col; ++j)
            maze[i][j] = str[j-1] - '0';
    }
}

void bfs(std::vector<std::vector<int>>& maze, int& row, int& col, FPos pos)
{
    const std::vector<FPos> dir = {{1,0},{0,1},{-1,0},{0,-1}};
    std::vector<std::vector<int>> dist(row + 1, std::vector<int>(col + 1, -1));
    std::queue<FPos> q;
    
    q.push(pos);
    dist[pos.y][pos.x] = 1;

    while(!q.empty())
    {
        FPos cur = q.front();
        q.pop();

        if (cur.x == col && cur.y == row)
        {
            std::cout<<dist[cur.y][cur.x];
            return;
        }
        
        for (int i = 0; i < 4; ++i)
        {
            FPos next = cur + dir[i];

            if (next.y > row || next.x > col ||
                next.y <= 0 || next.x <= 0)
                continue;

            if (maze[next.y][next.x] == 0)
                continue;

            if (dist[next.y][next.x] != -1)
                continue;

            dist[next.y][next.x] = dist[cur.y][cur.x] + 1;
            q.push(next);
        }
    }

}

int main()
{
    int row, col;
    std::vector<std::vector<int>> maze;
    input(maze, row, col);
    bfs(maze, row, col, {1, 1});
    return 0;
}