#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
#include <stack>
#include <iostream>

constexpr int INF = std::numeric_limits<int>::max();

int RecDFS(const std::vector<int>& footHold, int pos)
{
    if (pos == footHold.size() - 1)
        return 0;

    int cost1 = INF;
    int cost2 = INF;

    if (pos + 1 < footHold.size())
    {
        int step = std::abs(footHold[pos] - footHold[pos + 1]);
        cost1 = step + RecDFS(footHold, pos + 1);
    }

    if (pos + 2 < footHold.size())
    {
        int step = std::abs(footHold[pos] - footHold[pos + 2]);
        cost2 = step + RecDFS(footHold, pos + 2);
    }

    return std::min(cost1, cost2);
}

int StackDFS(const std::vector<int>& footHold)
{
    const int n = footHold.size();
    
    if(0== n)
        return 0;

    struct State
    {
        int pos;
        int cost;
    };

    std::stack<State> st;
    st.push({0,0});

    int minCost = INF;

    while(!st.empty())
    {
        State cur = st.top();
        st.pop();

        int pos = cur.pos;
        int cost = cur.cost;

        if(pos == n-1)
        {
            minCost = std::min(minCost,cost);
            continue;
        }

        if (pos + 1 < n)
        {
            int stepCost = std::abs(footHold[pos] - footHold[pos + 1]);
            st.push({pos + 1, cost + stepCost});
        }

        if (pos + 2 < n)
        {
            int stepCost = std::abs(footHold[pos] - footHold[pos + 2]);
            st.push({pos + 2, cost + stepCost});
        }
    }

    return minCost;
}

int DP(const std::vector<int>& footHold, int range)
{
    int n = footHold.size();
    std::vector<int> dp(n,INF);

    dp[0] = 0;

    for (int i = 1; i < n; ++i)
    {
        for (int j = 1; j <= range; ++j)
        {
            if (i - j < 0)
                break;

            int cost = dp[i-j] += std::abs(footHold[i]-footHold[i-j]);
            dp[i] = std::min(dp[i], cost);
        }
    }

    return dp[n-1];
}

int Step2DP(const std::vector<int>& footHold)
{
    int n = footHold.size();
    std::vector<int> dp(n, 0);

    dp[0] = 0;

    if (n > 1)
        dp[1] = std::abs(footHold[1] - footHold[0]);

    for (int i = 2; i < n; ++i)
    {
        int cost1 = dp[i - 1] + std::abs(footHold[i] - footHold[i - 1]);
        int cost2 = dp[i - 2] + std::abs(footHold[i] - footHold[i - 2]);
        dp[i] = std::min(cost1, cost2);
    }

    return dp[n - 1];
}

int main(void)
{
    std::vector<int> footHold;
    footHold = {8, 6, 9, 2, 1};
    // std::cout << RecDFS(footHold, 0);
    std::cout << StackDFS(footHold);
}