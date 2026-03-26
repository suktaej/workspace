#include <iostream>
#include <vector>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin>>n>>m;
    std::vector<std::vector<int>> grid(n + 1, std::vector<int>(n + 1));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            std::cin >> grid[i][j];

    std::vector<std::vector<long long>> sum(n + 1, std::vector<long long>(n + 1));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + grid[i][j];

    for(int i=0;i<m;++i)
    {
        int x1,y1,x2,y2;
        std::cin>>x1>>y1>>x2>>y2;
        
        long long res = sum[x2][y2] - sum[x1-1][y2] -sum[x2][y1-1] + sum[x1-1][y1-1];
        
        std::cout<<res<<'\n';
    }

    return 0;
}