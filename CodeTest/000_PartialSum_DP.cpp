#include <array>
#include <vector>
#include <iostream>
#include <limits>

constexpr int INF = std::numeric_limits<int>::max();

bool DP2D(int total, std::vector<int>& cards)
{
    int num = cards.size();
    // 가능성
    std::vector<std::vector<bool>> dp(num + 1, std::vector<bool>(total + 1, false));
    dp[0][0] = true;

    // n개의 카드를 조합했을 경우
    for (int i = 1; i <= num; ++i)
    {
        int cardValue = cards[i - 1];
        // 합이 구성되는가?
        for (int j = 0; j <= total; ++j)
        {
            // 미선택
            dp[i][j] = dp[i-1][j];
            // 선택
            if(j >= cardValue)
                dp[i][j] = dp[i][j] || dp[i - 1][j - cardValue];
        }
    }

    return dp[num][total];
}

bool DP1D(int total, std::vector<int>& cards)
{
    std::vector<bool> dp(total + 1, false);

    for(int card : cards)
    {
        for(int i = total; i >= card; --i)
            dp[i] = dp[i] | dp[i - card];

        if(dp[total])
            return true;
    }

    return dp[total];
}

int main()
{
    std::vector<int> cards = {2,5,9};
    int sum = 16;
    return 0;
}