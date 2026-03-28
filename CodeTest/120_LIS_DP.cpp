#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

int n;
std::vector<int> arr;

void solve()
{
    std::vector<int> dp(n,1);
    std::vector<int> prev(n,-1);
    int maxLen = 0;
    int maxIdx = -1;
    
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<i;++j)
            if (arr[j] < arr[i])
            {    // dp[i] = std::max(dp[j]+1,dp[i]);
                if(dp[i] < dp[j]+1)
                {
                    dp[i] = dp[j]+1;
                    prev[i] = j;
                }
            }    
            
        // maxLen = std::max(dp[i],maxLen);
        if(dp[i] > maxLen)    
        {
            maxLen = dp[i];
            maxIdx = i;
        }
    }
    
    std::cout<<maxLen<<'\n';
    
    std::stack<int> path;
    
    for(int i = maxIdx;i!=-1;i=prev[i])
        path.push(arr[i]);
    
    while(!path.empty())
    {
        std::cout<<path.top()<<" ";
        path.pop();
    }
}

int main()
{
    std::cin>>n;
	arr.resize(n);
	for(int i=0; i<n; ++i)
		std::cin>>arr[i];

    solve();
	return 0;
}