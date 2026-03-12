#include <iostream>
#include <vector>

constexpr int maxSize = 15;
int board[maxSize+1][maxSize+1] = {0, };
int size;

void displacement(int row, int col, int sign)
{
    int rPos = col;
    int lPos = col;

    for (int i = row + 1; i <= size; ++i)
    {
        board[i][col]+=sign;

        if(--lPos >= 1)
            board[i][lPos]+=sign;

        if(++rPos <= size)
            board[i][rPos]+=sign;
    }

}

int dfs(int row)
{
    if(row > size)
        return 1;

    int cnt = 0;

    for (int j = 1; j <= size; ++j)
    {
        if (board[row][j] == 0)
        {
            displacement(row, j, 1);
            cnt += dfs(row+1);
            displacement(row, j, -1);
        }
    }

    return cnt;
}

int main()
{
    std::cin>>size;
    
    int res = 0;

    res += dfs(1);
    std::cout<<res;

    return 0;
}