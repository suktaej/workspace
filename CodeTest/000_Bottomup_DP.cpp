#include <vector>
#include <iostream>
#include <limits>

std::vector<int> cost = {10,15,20,5};
constexpr int INF = std::numeric_limits<int>::max();
constexpr int STEP = 2;

int DP()
{
    int size = cost.size();
    std::vector<int> dp(size,INF);

    dp[0] = 0;
/*    
    if(size > 1)
        dp[1] = dp[0] + cost[0];

    for(int i = 2; i<size; ++i)
    {
        int cost1 = dp[i-1]+cost[i-1];
        int cost2 = dp[i-2]+cost[i-2];
        dp[i] = std::min(cost1,cost2);
    }
*/
    for (int i = 1; i < size; ++i)
    {
        for (int j = 1; j <= STEP; ++j)
        {
            if (i - j < 0)
                break;
            
            int newCost = dp[i-j] + cost[i-j];
            dp[i] = std::min(dp[i],newCost);
        }
    }
    return dp[size-1];
}

int main()
{
    std::cout<<DP();
    return 0;
}
