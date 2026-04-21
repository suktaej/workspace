#include <iostream>
#include <vector>
#include <cmath>

int n, r, c;
int cnt = 0;
std::vector<std::vector<int>> grid;

int ans = 0;

void dfs(int exp, int row, int col)
{
    if(exp == 1)
    {
        grid[row][col] = cnt++;
        grid[row][col+1] = cnt++;
        grid[row+1][col] = cnt++;
        grid[row+1][col+1] = cnt++;

        if(grid[r][c]!=0)
            std::cout<<grid[r][c];

        return;
    }

    int newExp = exp-1;
    int nextSize = pow(2,newExp);

    dfs(newExp, row, col);
    dfs(newExp, row, col+nextSize);
    dfs(newExp, row+nextSize, col);
    dfs(newExp, row+nextSize, col+nextSize);
}

void solve(int size, int x, int y)
{
    if (y == r && x == c)
    {
        std::cout<< ans;
        return;
    }

    if (r >= y && r < y + size && c >= x && c < x + size) 
    {
        int nextSize = size / 2;
        solve(y, x, nextSize);
        solve(y, x + nextSize, nextSize);
        solve(y + nextSize, x, nextSize);
        solve(y + nextSize, x + nextSize, nextSize);
    } 
    else
        ans += size * size;
}
int main()
{
    std::cin>>n>>r>>c;
    solve((1<<n),0,0);

    return 0;
}