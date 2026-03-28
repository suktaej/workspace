#include <iostream>
#include <vector>

int n , m;
std::vector<int> prefixSum;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cin>>n>>m;
    prefixSum.resize(n+1);

    for(int i=1;i<=n;++i)
    {
        int num;
        std::cin>>num;
        
        prefixSum[i] = prefixSum[i - 1] + num;
    }

    for(int i=0;i<m;++i)
    {
        int low, high;
        std::cin>>low>>high;
        
        int res = prefixSum[high] - prefixSum[low-1];
        std::cout<<res<<'\n';
    }

    return 0;
}