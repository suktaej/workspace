    #include <iostream>
    #include <vector>
    #include <algorithm>

    int n;
    constexpr int houseColor = 3;
    std::vector<std::vector<int>> colors;

    void input()
    {
        std::cin>>n;
        colors.resize(n,std::vector<int>(houseColor,0));
        
        for(int i=0;i<n;++i)
            for(int j=0;j<houseColor;++j)
                std::cin>>colors[i][j];
    }

    void bottomUp()
    {
        std::vector<std::vector<int>> dp(n,std::vector<int>(houseColor));

        dp[0][0] = colors[0][0];
        dp[0][1] = colors[0][1];
        dp[0][2] = colors[0][2];

        for(int i=1;i<n;++i)
        {
            dp[i][0] = std::min(dp[i-1][1], dp[i-1][2]) + colors[i][0];
            dp[i][1] = std::min(dp[i-1][2], dp[i-1][0]) + colors[i][1];
            dp[i][2] = std::min(dp[i-1][0], dp[i-1][1]) + colors[i][2];
        }

        std::cout<<std::min({dp[n-1][0], dp[n-1][1], dp[n-1][2]});
    }

    int main()
    {
        input();
        bottomUp();
        return 0;
    }