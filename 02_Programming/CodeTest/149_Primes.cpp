#include <iostream>
#include <algorithm>
#include <cmath>

constexpr int constraint = 123456*2;
int nums[constraint+1];

int main()
{
    std::ios::sync_with_stdio(false); std::cin.tie(NULL);
    std::fill(std::begin(nums),std::end(nums),1);
    
    int lim = std::sqrt(constraint);
    nums[0] = 0;
    nums[1] = 0;

    for(int i=2;i<=lim;++i)
        if(nums[i])
            for (int j = i * i; j <= constraint; j += i)
                nums[j] = 0;

    for(int i=1;i<=constraint;++i)
        nums[i] += nums[i-1];

    while(true)
    {
        int n;
        std::cin>>n;

        if(n==0)
            break;

        std::cout<<nums[2*n]-nums[n]<<'\n';
    }
    
    return 0;
}