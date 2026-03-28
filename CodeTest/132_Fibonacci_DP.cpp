#include <iostream>
#include <cstdio>
#include <vector>

std::pair<int,int> dp[41] = {};

void fibonacci() 
{
    dp[0] = {1,0};
    dp[1] = {0,1};

    for(int i=2;i<=40;++i)
        dp[i] = {dp[i-1].first + dp[i-2].first,
        dp[i-1].second + dp[i-2].second};
}

int main()
{
    int testCase;
    scanf_s("%d",&testCase);
        
    fibonacci();

    for(int i=0;i<testCase;++i)
    {
        int num;
        scanf_s("%d",&num);
        std::cout << dp[num].first << ' ' << dp[num].second << '\n';
    }

    return 0;
}