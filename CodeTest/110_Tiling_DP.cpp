#include <iostream>
#include <vector>

int n;
std::vector<int> map[2];
std::vector<int> dpMap;

int dfs()
{
    int r = -1;
    int c = -1;

    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (map[i][j] == 0)
            {
                r = i;
                c = j;
                break;
            }
        }
        if (r != -1)
            break;
    }

    if(r == -1)
        return 1;

    int res = 0;

    if (c + 1 < n && map[r][c + 1] == 0)
    {
        map[r][c] = 1;
        map[r][c+1] = 1;
        
        res += dfs();

        map[r][c] = 0;
        map[r][c+1] = 0;
    }

    if (r + 1 < 2 && map[r + 1][c] == 0)
    {
        map[r][c] = 1;
        map[r + 1][c] = 1; 
        
        res += dfs();

        map[r][c] = 0;
        map[r + 1][c] = 0;
    }

    return res;
}

int topDown(int w)
{
    // base case
    if (w <= 1)
        return 1;

    // memo
    if(dpMap[w] != -1)
        return dpMap[w];

    // init

    // loop
    dpMap[w] = topDown(w-1) + topDown(w-2);

    return dpMap[w];
}

int bottomUp(int w)
{
    dpMap[0] = 1;
    dpMap[1] = 1;

    for(int i=2; i<=w;++i)
        dpMap[i] = dpMap[i-1]+dpMap[i-2];

    return dpMap[w];
}

int main()
{
    std::cin >> n;
    dpMap.assign(n+1,-1);

    std::cout<< topDown(n);

    return 0;
}