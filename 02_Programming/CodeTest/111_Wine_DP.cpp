#include <iostream>
#include <vector>
#include <algorithm>

int n;
std::vector<int> cost;

void singleDP()
{
    std::vector<int> dp(n+1);

    dp[1] = cost[1];
    dp[2] = dp[1] + cost[2];

    for(int i=3;i<=n;++i)
        dp[i] = std::max({
            dp[i-1],
            dp[i-2]+cost[i], 
            dp[i-3]+cost[i-1]+cost[i]});
    
    std::cout<<dp[n];
}

void doubleDP()
{
    std::vector<std::vector<int>> dp(n+1,std::vector<int>(3,0));

    dp[1][0] = 0;
    dp[1][1] = cost[1];
    dp[1][2] = 0;

    for(int i=2;i<=n;++i)
    {
        dp[i][0] = std::max({dp[i - 1][0], dp[i - 1][1], dp[i - 1][2]});
        dp[i][1] = dp[i - 1][0] + cost[i];
        dp[i][2] = dp[i - 1][1] + cost[i];
    }

    std::cout<< std::max({dp[n][0],dp[n][1],dp[n][2]});
}

int main()
{
    std::cin>>n;
    cost.resize(n+1);

    for(int i=1;i<=n;++i)
        std::cin>>cost[i];

    singleDP();
    return 0;
}