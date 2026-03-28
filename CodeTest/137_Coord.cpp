#include <iostream>
#include <algorithm>
#include <vector>

void solve()
{
    int n;
    std::cin>>n;

    std::vector<int> nums(n);
    std::vector<int> sorted(n);

    for(int i=0;i<n;++i)
    {
        std::cin>>nums[i];
        sorted[i] = nums[i];
    }

    std::sort(sorted.begin(),sorted.end());
    sorted.erase(std::unique(sorted.begin(),sorted.end()),sorted.end());

    for(int i =0;i<n;++i)
    {
        auto it = lower_bound(sorted.begin(),sorted.end(),nums[i]);
        std::cout<<(it-sorted.begin())<<' '; 
    }
}

int main()
{
    solve();
    return 0;
}