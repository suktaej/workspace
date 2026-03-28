#include <iostream>
#include <algorithm>
#include <vector>

void prefixSum()
{
    int total;
    std::cin>>total;
    
    int cur = 0;
    int min = 0;
    int res = -1e9;

    for(int i =1; i<=total;++i)
    {
        int temp;
        std::cin>>temp;
        cur += temp;

        res = std::max(res, cur - min);
        min = std::min(min, cur);
    }

    std::cout << res;
}

void dp()
{
    int total;
    int temp;
    // int res = -1e9;
    // int max;
    
    std::cin>>total;
    std::cin>>temp;
    
    int max = temp;
    int res = temp;

    for(int i=2;i<=total;++i)
    {
        std::cin>>temp;
        
        // if(i == 1)
        //     max = temp;
        // else
        max = std::max(temp, max + temp);
        res = std::max(res, max);
    }

    std::cout<<res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    dp();
    return 0;
}