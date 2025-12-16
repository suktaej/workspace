#include <vector>
#include <limits>

const std::vector<int> cost = {10,15,20,5};
constexpr int INF = std::numeric_limits<int>::max();

int DP()
{
    int size = cost.size();
    std::vector<int> dp(size,INF);

    dp[0] = 0;
    
    if(size > 1)
        dp[1] = dp[0] + cost[0];

    for(int i = 2; i<size; ++i)
    {
        int cost1 = dp[i-1]+cost[i-1];
        int cost2 = dp[i-2]+cost[i-2];
        dp[i] = std::min(cost1,cost2);
    }

    return dp[size-1];
}

int main()
{
    return 0;
}
