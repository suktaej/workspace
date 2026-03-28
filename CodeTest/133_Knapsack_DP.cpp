#include <iostream>
#include <vector>
#include <algorithm>

int N, K;

void bottomUp()
{
    std::cin>>N>>K;
    std::vector<std::pair<int, int>> items({});

    for(int i=0;i<N;++i)
    {
        int w, v;
        std::cin>>w>>v;
        items[i] = {w, v};
    }

    std::vector<std::vector<int>> dp(N+1,std::vector<int>(K+1));

    for(int i=1;i<=N;++i)
    {
        const auto& [weight,value] = items[i-1];
        for(int j=1;j<=K;++j)
        {
            if (j >= weight)
                dp[i][j] = std::max(dp[i - 1][j], value + dp[i - 1][j - weight]);
            else
                dp[i][j] = dp[i-1][j];
        }
    }
    
    std::cout<<dp[N][K];
}

void optimize()
{
    std::cin>>N>>K;
    std::vector<int> dp(K+1);

    for(int i=0;i<N;++i)
    {
        int weight, value;
        std::cin>>weight>>value;

        for (int j = K; j >= weight; --j)
            dp[j] = std::max(dp[j],value + dp[j-weight]);
            // if(dp[j-weight] + value > dp[j])
            //     dp[j] = dp[j-weight] + value;
    }

    std::cout<<dp[K];

}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    // bottomUp();
    optimize();

    return 0;
}