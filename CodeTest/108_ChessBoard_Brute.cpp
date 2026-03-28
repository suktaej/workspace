#include <iostream>
#include <vector>
#include <queue>
#include <string>

int n, m;
std::vector<std::string> board;

struct FBestSquare
{
    int cnt;
    int x;
    int y;
};

int matchCnt(int y, int x, char color)
{
    int repaint = 0;

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            char expected;

            if ((i + j) % 2 == 0)
                expected = color;
            else
                expected = (color=='W') ? 'B' : 'W';

            if(board[y+i][x+j] != expected)
                ++repaint;
        }
    }

    return repaint;
}

int main()
{
    std::cin >> n >> m;

    board.resize(n,"");

    for (int i = 0; i < n; ++i)
        std::cin >> board[i];

    FBestSquare pos = {64, -1, -1};

    for (int i = 0; i <= n-8; ++i)
    {
        for (int j = 0; j <= m-8; ++j)
        {
            int caseW = matchCnt(i, j, 'W');
            int caseB = matchCnt(i, j, 'B');
            int curMin = std::min(caseW, caseB);

            if(pos.cnt > curMin)
                pos = {curMin, j, i};
        }
    }

    std::cout<<pos.cnt;

    return 0;
}