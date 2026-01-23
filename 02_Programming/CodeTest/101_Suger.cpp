#include <iostream>
#include <vector>

// DP문항
// 최소값 비교가 필요하므로 최대값으로 초기화
// 배열 내 모든 값을 누적하는 방식으로 구현

int main()
{
    int n;
    std::cin>>n;

    std::vector<int> dp(n + 1, 1e9);

    dp[0] = 0;
    // dp[3] = 1;
    // dp[5] = 1;

    for (int i = 3; i <= n; i++)
            dp[i] = std::min(dp[i], dp[i - 3] + 1);

    for (int i = 5; i <= n; i++) 
            dp[i] = std::min(dp[i], dp[i - 5] + 1);

    if (dp[n] >= 1e9) 
        std::cout << -1;
    else 
        std::cout << dp[n];

    return 0;
}