#include <iostream>
#include <vector>

void solve()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin>>n;
    constexpr int dgt = 10;
    constexpr int mod = 1000000000;

    std::vector<std::vector<long long>> dp(n+1,std::vector<long long>(dgt,0));

    for (int i = 1; i < dgt; ++i)
        dp[1][i] = 1;

    for (int i = 2; i <= n; ++i)
    {
        for (int j = 0; j < dgt; ++j)
        {
            if (j == 0)
                dp[i][0] = dp[i - 1][1] % mod;
            else if (j == 9)
                dp[i][9] = dp[i-1][8] % mod;
            else
                dp[i][j] = (dp[i-1][j-1] + dp[i-1][j+1]) % mod;
        }
    }

    int res = 0;

    for (int i = 0; i < dgt; ++i)
        res = (res + dp[n][i]) % mod;

    std::cout << res;
}

int main()
{
    solve();
    return 0;
}