#include <iostream>
#include <vector>

int col;
std::vector<int> tile;

int topDown(int n)
{
    if(n < 0)
        return 0;
    
    if(n == 0)
        return 1;

    if(tile[n]!= -1)
        return tile[n];

    // tile[n] = topDown(n-1) + 2*topDown(n-2) + topDown(n-3);
    tile[n] = topDown(n-1) + 2*topDown(n-2);

    return tile[n];
}

void bottomUp()
{
    int blocks[] = {1,2,2};
    
    tile[0] = 1;

    for(int i=1;i<=col;++i)
        for(int block : blocks)
            if(i-block >= 0)
                tile[i] += tile[i-block];

    std::cout<<tile[col];
}

int main()
{
    std::cin>>col;
    tile.resize(col + 1, -1);

    std::cout<<topDown(col)<<'\n';
    
    tile.assign(col+1 , 0);

    bottomUp();
    
    return 0;
}