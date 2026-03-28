#include <array>
#include <vector>

const std::array<int,5> cost = {2,5,3,3,1};
constexpr int TERM = 2;

int DP()
{
    int size = cost.size();
    std::vector<int> dp(size + 1, 0);
    dp[0] = 0;

    for(int i = 1; i<=size;++i)
    {
        //미선택
        dp[i] = dp[i-1];
        //선택
        if (i >= TERM)
            dp[i] = std::max(dp[i], dp[i - TERM] + cost[i - 1]);
        else
            dp[i] = std::max(dp[i], cost[i-1]);
    }

    return dp[size];
}

int main()
{
    return 0;
}