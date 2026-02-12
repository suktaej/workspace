#include <iostream>
#include <vector>
#include <string>
#include <queue>

int n, m;
std::vector<std::vector<int>> board;

void input()
{
    std::cin >> m >> n;
    board.resize(n, std::vector<int>(m));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            std::cin >> board[i][j];
}

int layerBFS()
{
    std::queue<std::pair<int, int>> q;
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    int date = 0;
    int unripe = 0;

    // init
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (board[i][j] == 1)
                q.push({i, j});
            else if (board[i][j] == 0)
                ++unripe;

    while (!q.empty())
    {
        // 현재 큐에 있는 개수만큼만 반복
        int size = q.size();
        bool progressed = false;

        for (int i = 0; i < size; ++i)
        {
            auto [cy, cx] = q.front();
            q.pop();

            for (int d = 0; d < 4; ++d)
            {
                int ny = cy + dy[d];
                int nx = cx + dx[d];

                if (ny >= 0 && ny < n && nx >= 0 && nx < m)
                {
                    if (board[ny][nx] == 0)
                    {
                        board[ny][nx] = 1;
                        unripe--;
                        q.push({ny, nx});
                        progressed = true;
                    }
                }
            }
        }
        
        if (progressed)
            ++date;
    }

    if (unripe > 0)
        return -1;

    return date;
}

int optBFS()
{
    std::queue<std::pair<int, int>> q;
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    int date = 0;
    int unripe = 0;

    // init
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (board[i][j] == 1)
                q.push({i, j});
            else if (board[i][j] == 0)
                ++unripe; // 0을 수집

    while (!q.empty())
    {
        auto [cy, cx] = q.front();
        q.pop();
        date = board[cy][cx] - 1; // 최후에 pop되는 값이 최종값

        for (int i = 0; i < 4; ++i)
        {
            int ny = cy + dy[i];
            int nx = cx + dx[i];

            if (ny >= n || ny < 0 || nx >= m || nx < 0)
                continue;

            if (board[ny][nx] == 0)
            {
                board[ny][nx] = board[cy][cx] + 1;
                --unripe; // 전이되면 감소
                q.push({ny, nx});
            }
        }
    }

    if (unripe > 0)
        return -1;

    return date;
}

int bfs()
{
    std::queue<std::pair<int, int>> q;
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    // init
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (board[i][j] == 1)
                q.push({i, j});

    while (!q.empty())
    {
        auto [cy, cx] = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i)
        {
            int ny = cy + dy[i];
            int nx = cx + dx[i];

            if (ny >= n || ny < 0 || nx >= m || nx < 0)
                continue;

            if (board[ny][nx] == 0)
            {
                board[ny][nx] = board[cy][cx] + 1;
                q.push({ny, nx});
            }
        }
    }

    int date = 0;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (board[i][j] == 0)
                return -1;

            if (board[i][j] > date)
                date = board[i][j];
        }
    }

    return date - 1;
}

int main()
{
    input();
    std::cout << bfs();
    return 0;
}