#include <iostream>
#include <vector>
#include <queue>
#include <string>

int n, m;
std::vector<std::string> board;

void makeDiff(std::vector<std::vector<int>>& diffBoard)
{
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            char expected = ((i + j) % 2 == 0) ? 'W' : 'B';
            int diffVal = board[i-1][j-1] != expected;

            diffBoard[i][j] = diffVal + diffBoard[i-1][j] + diffBoard[i][j-1] - diffBoard[i-1][j-1];
        }
    }
}

void searchBestMatch(std::vector<std::vector<int>>& diff)
{
    int res = 64;

    for (int i = 1; i <= n - 7; ++i)
    {
        for (int j = 1; j <= m - 7; ++j)
        {
            int row = i;
            int col = j;
            int y = i+7;
            int x = j+7;

            int repaint = diff[y][x] - diff[row-1][x] - diff[y][col-1] + diff[row-1][col-1];
            int curMin = std::min(repaint, 64-repaint);
            res = std::min(res, curMin);
        }
    }
    std::cout<<res;
}

int main()
{
    std::cin >> n >> m;

    board.resize(n,"");

    for (int i = 0; i < n; ++i)
        std::cin >> board[i];

    std::vector<std::vector<int>> diffBoard(n + 1, std::vector<int>(m + 1, 0));
    makeDiff(diffBoard);
    searchBestMatch(diffBoard);

    return 0;
}