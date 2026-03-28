#include <iostream>
#include <algorithm>
#include <vector>

void solve()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin>>n;
    std::vector<std::pair<int,int>> sche(n);
    std::vector<int> dp(n+2);

    for(int i=0;i<n;++i)
    {
        int per, pay;
        std::cin>>per>>pay;
        sche[i] = {per,pay};
    }

    int s = sche.size();
    
    for (int i = n; i > 0; --i)
    {
        auto [period, income] = sche[i - 1];
        if (period + i <= n + 1)
            dp[i] = std::max(dp[i+1], dp[i + period] + income);
        else
            dp[i] = dp[i+1];
    }

    std::cout<<dp[1];
}

int main()
{
    solve();
    return 0;
}