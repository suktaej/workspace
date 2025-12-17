#include <vector>
#include <limits>
#include <array>
#include <cstdlib>

const std::array<int,5> height = {8, 6, 9, 2, 1};
constexpr int STEP = 2;
constexpr int INF = std::numeric_limits<int>::max();

int BottomUp()
{
    int size = height.size();
    std::vector<int> dp(size, INF);

    dp[0] = 0;

    for(int i=1;i<size;++i)
    {
        for(int j=1;j<=STEP;++j)
        {
            if(i-j < 0)
                break;

            int acc = dp[i - j] + std::abs(height[i] - height[i - j]);
            dp[i] = std::min(dp[i],acc);      
        }
    }

    return dp[size-1];
}

std::vector<int> memo(height.size(), -1);

int DFS(int pos)
{
    if (pos >= height.size() - 1)
        return 0;

    if (memo[pos] != -1)
        return memo[pos];

    int res = INF;

    for(int i=1;i<=STEP;++i)
    {
        if(pos+i < height.size())
        {
            int cost = DFS(pos+i) + std::abs(height[pos]-height[pos+i]);
            res = std::min(res,cost);
        }
    }

    return memo[pos] = res;
}