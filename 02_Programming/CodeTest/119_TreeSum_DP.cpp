#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> tree;
std::vector<std::vector<int>> dp;
int n;

void treeTopDown()
{
    dp[0][0] = tree[0][0];

    for(int i=1;i<n;++i)
    {
        for(int j=0;j<=i;++j)
        {
            if(j==0)
                dp[i][j] = tree[i][j] + dp[i-1][j];
            else if(j==i)
                dp[i][j] = tree[i][j] + dp[i-1][j-1];
            else
                dp[i][j] = tree[i][j] + std::max(dp[i-1][j-1], dp[i-1][j]);
        }
    }

    int res = 0;
    for(int i=0;i<n;++i)
        res = std::max(res, dp[n-1][i]);
        
    std::cout<<res;
}

void treeBottomUp()
{
    for (int i = n - 2; i >= 0; --i) 
    {
        for (int j = 0; j <= i; ++j)
            tree[i][j] += std::max(tree[i + 1][j], tree[i + 1][j + 1]);
    }
}

int main()
{
    std::cin>>n;
    tree.resize(n);
    dp.resize(n);
    
    for(int i=0;i<n;++i)
    {
        tree[i].resize(i+1);
        dp[i].resize(i+1);
        
        for(int j=0;j<=i;++j)
            std::cin>>tree[i][j];
    }

    treeBottomUp();
    
    return 0;
}