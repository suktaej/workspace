#include <iostream>
#include <vector>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin>>n;

    if (n == 1)
    {
        std::cout << 1;
        return 0;
    }

    // std::vector<std::vector<long long>> dp(2,std::vector<long long>(n+1));
    std::vector<int> dp(n+1);

    // dp[0][1] = 0;
    // dp[1][1] = 1;
    // dp[0][2] = 1;
    // dp[1][2] = 1;
    dp[1] = 1;
    dp[2] = 2;

    for(int i = 3; i<=n; ++i)
    {
        // dp[0][i] = (dp[0][i-2] + dp[1][i-2]) % 15746;
        // dp[1][i] = (dp[0][i-1] + dp[1][i-1]) % 15746;
        dp[i] = (dp[i-1]+dp[i-2]) % 15746;
    }

    // std::cout << (dp[0][n] + dp[1][n]) % 15746;
    std::cout<<dp[n];

    return 0;
}