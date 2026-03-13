#include <iostream>
#include <vector>

int inp;
constexpr int height = 3;
std::vector<std::vector<long long>> dp;

void gen(int col, int row, int curMask, int nextMask)
{
    if(row == height)
    {
        dp[col+1][nextMask] += dp[col][curMask];
        return;
    }

    if (curMask & (1 << row))
        gen(col, row+1, curMask, nextMask);
    else
    {
        // 2x1 block set
        gen(col, row+1, curMask, nextMask | (1<<row));

        // 1x2 block set
        if (row + 1 < height &&
            !(curMask & (1 << (row + 1))))
            gen(col, row+2, curMask, nextMask);
    }
}

void tripleSolve()
{
    std::cin >> inp;

    if (inp % 2 != 0)
    {
        std::cout << 0;
        return;
    }

    constexpr int state = 1 << height;
    dp.assign(inp+1, std::vector<long long>(state,0));

    dp[0][0] = 1;

    for (int i = 0; i < inp; ++i)
        for (int m = 0; m < state; ++m)
            if (dp[i][m] > 0)
                gen(i,0,m,0);

    std::cout<<dp[inp][0];
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    tripleSolve();
    return 0;
}