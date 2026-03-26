#include <iostream>
#include <vector>

int main()
{
    int n;
    std::cin>>n;
    // std::vector<long> dp(n);
    // dp[0] = 1;
    // dp[1] = 1;

    // for(int i=2;i<n;++i)
    //     dp[i] = dp[i-1]+dp[i-2];

    // std::cout<<dp[n-1];

    std::vector<std::vector<long long>> dp(n + 1, std::vector<long long>(2));

    dp[1][0] = 0;
    dp[1][1] = 1;

    for(int i=2;i<=n;++i)
    {
        dp[i][0] = dp[i-1][0] + dp[i-1][1];
        dp[i][1] = dp[i-1][0];
    }

    std::cout<<dp[n][0]+dp[n][1];
}