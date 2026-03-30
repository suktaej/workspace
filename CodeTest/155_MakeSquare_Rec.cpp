#include <iostream>
#include <cmath>
#include <vector>

int n;
std::vector<std::vector<char>> grid;

void solve(int n, int row, int col)
{
    if(n == 1)
    {
        grid[row][col] = '*';
        return;
    }

    int nextSize = n / 3;

    for(int i=0;i<3;++i)
    {
        for(int j =0;j<3;++j)
        {
            if (i == 1 && j == 1)
                continue;

            solve(nextSize, row+(i*nextSize), col+(j*nextSize));
        }
    }
    /*
    for (int k = 3; k <= n; k *= k)
    {
        int upper = k / 3;
        int lower = 2 * (k / 3);

        for(int i = 1; i <= k; ++i)
        {
            for (int j = 1; j <= k; ++j)
            {
                if(i<=upper || i>lower)
                    grid[i][j] = '*';
                else
                {
                    if(j<=upper || j>lower)
                        grid[i][j] = '*';
                    else
                        grid[i][j] = ' ';
                }
            }
        }
    }
    */


}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n;
    grid.assign(n, std::vector<char>(n, ' '));

    solve(n,0,0);
    
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
            std::cout << grid[i][j];
        std::cout << '\n';
    }
    return 0;
}
