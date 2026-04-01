#include <iostream>
#include <queue>
#include <vector>

int n;
int blue = 0;
int white = 0;
std::vector<std::vector<int>> grid;

void dfs(int y, int x, int size)
{
    int color = grid[y][x];
    bool flag = true;

    for(int i=y;i<y+size;++i)
    {
        for(int j=x;j<x+size;++j)
        {
            if(color!=grid[i][j])
            {
                flag = false;
                break;
            }
        }
        if(!flag)
            break;
    }

    if(flag)
    {
        if(color==1)
            ++blue;
        else
            ++white;
    }
    else
    {
        int nextSize = size / 2;
        dfs(y,x,nextSize);
        dfs(y, x + nextSize, nextSize); 
        dfs(y + nextSize, x, nextSize);
        dfs(y + nextSize, x + nextSize, nextSize);
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin>>n;
    grid.resize(n,std::vector<int>(n,0));

    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
            std::cin>>grid[i][j];

    dfs(0,0,n);

    std::cout<<white<<'\n'<<blue;

    return 0;
}