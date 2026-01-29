#include <iostream>
#include <vector>

int main()
{
    int n, k;
    std::cin >> n;
    std::vector<int> t;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> k;
        t.push_back(k);
    }

    for(const int i : t)
    {
        std::vector<int> dp(i + 1, 0);

        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 4;

        for (int j = 4; j <= i; ++j)
            dp[j] = dp[j-1]+dp[j-2]+dp[j-3];

        std::cout<<dp[i]<<std::endl;
    }

    return 0;
}