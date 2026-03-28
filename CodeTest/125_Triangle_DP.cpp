#include <vector>
#include <iostream>

int main()
{
    constexpr int max = 101;
    std::vector<long long> dp(max,0);
    dp[1] = 1;
    dp[2] = 1;
    dp[3] = 1;

    for (int j = 4; j <= max; ++j)
        dp[j] = dp[j - 2] + dp[j - 3];
    
    int testCase;
    std::cin>>testCase;
    
    for(int i=0;i<testCase;++i)
    {
        int temp;
        std::cin>>temp;
        std::cout<<dp[temp]<<'\n';
    }

    return 0;
}