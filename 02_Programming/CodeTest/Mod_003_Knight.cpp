#include <iostream>
#include <vector>

struct FPos
{
    int x, y;
};

constexpr int SIZE = 7;
constexpr FPos START = {0,0};

int DP(int row, int col,FPos start)
{
    std::vector<std::vector<int>> grid(row, std::vector<int>(col, 0));
    grid[start.y][start.x] = 1;

    for (int y = start.y; y < row; ++y)
    {
        for (int x = start.x; x < col; ++x)
        {
            if(x == start.x && y == start.y)
                continue;

            int left = (x > start.x ? grid[y][x - 1] : 0);
            int down = (y > start.y ? grid[y - 1][x] : 0);
            grid[y][x] = left + down;
        }
    }

    return grid[row-1][col-1];
}

int combination(int n, int r)
{
    if (r > n)
        return 0;

    r = std::min(r, n - r);
    
    int res = 1;

    for (int i = 0; i < r; ++i)
        res = res * (n-i) / (i+1);

    return res;
}

int knightDP(int row, int col, FPos start)
{
    std::vector<std::vector<int>> grid(row, std::vector<int>(col,0));
    grid[start.y][start.x] = 1;

    for (int y = start.y; y < row; ++y)
    {
        for (int x = start.x; x < col; ++x)
        {
            if(start.x == x && start.y == y)
                continue;

            int rru = 0;
            int uur = 0;

            if (x >= 2 && y >= 1)
                rru = grid[y-1][x-2];

            if (x >= 1 && y >= 2)
                uur = grid[y-2][x-1];

            grid[y][x] = rru + uur;
        }
    }

    return grid[row-1][col-1];
}

int knightCombination(int row, int col)
{
    // 나이트의 이동
    FPos moveA = {2, 1}; // rru
    FPos moveB = {1, 2}; // uur

    // 분모 계산
    int det = (moveA.x * moveB.y) - (moveB.x * moveA.y);

    // 분자 계산
    int molecularA = (moveB.y * col - moveB.x * row);
    int molecularB = (moveA.x * row - moveA.y * col);

    // 예외 처리
    if (molecularA % det != 0 || molecularB % det != 0) 
        return 0;
    
    int a = molecularA / det;
    int b = molecularB / det;

    if (a < 0 || b < 0) 
        return 0;

    // 조합 계산
    return combination(a + b, a);
}

int main()
{
    std::cout<<DP(SIZE, SIZE, START);
    std::cout<<'\n';
    std::cout << combination((SIZE - 1) * 2, SIZE - 1);
    std::cout<<'\n';
    std::cout<<knightDP(SIZE,SIZE,START);
    std::cout<<'\n';
    std::cout << knightCombination(SIZE - 1, SIZE - 1);
    return 0;
}