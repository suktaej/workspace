#include <iostream>
#include <vector>

// Greed로 풀 수 없으므로 DP

int main(void)
{
    int n;
    std::cin>> n;
    // 0이 아닌 1번을 탐색해야 하므로
    std::vector<int> dp(n + 1);

    // 인덱스는 해당 값
    // 값은 탐색 횟수
    dp[1] = 0;

    for (int i = 2; i <= n; ++i)
    {
        // 1을 빼는 연산을 수행했을 경우를 우선 가정
        dp[i] = dp[i - 1] + 1;

        // 2로 나누어 떨어지면 2로 나눈 경우와 비교
        if (i % 2 == 0)
            dp[i] = std::min(dp[i], dp[i / 2] + 1);

        // 3으로 나누어 떨어지면 3으로 나눈 경우와 비교
        if (i % 3 == 0)
            dp[i] = std::min(dp[i], dp[i / 3] + 1);
    }

    std::cout << dp[n];
    return 0;
}