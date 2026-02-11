#include <iostream>
#include <vector>

std::vector<int> cost;
int n;

void bottomUP()
{
    std::vector<int> dp(n+1);
    dp[1] = cost[1];
    dp[2] = cost[1]+cost[2];
    dp[3] = std::max(cost[1]+cost[2], cost[2]+cost[3]);

    for(int i=4;i<=n;++i)
        dp[i] = std::max(dp[i-2]+cost[i], dp[i-3]+cost[i-1]+cost[i]);

    std::cout<<dp[n];
}

int main()
{
    std::cin>>n;
    cost.resize(n+1);

    cost[0] = 0;
    for(int i=1;i<=n;++i)
        std::cin>>cost[i];
    
    bottomUP();

    return 0;
}