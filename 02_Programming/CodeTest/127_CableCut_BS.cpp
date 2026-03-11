#include <iostream>
#include <vector>
#include <algorithm>
// #include <bits/stdc++.h>
    
int have, need;
std::vector<long> lines;

void bs(long base)
{
    long long res = 0;
    long left = 1;
    long right = base;

    while(left <= right)
    {
        long mid = left + (right - left) / 2;
        long long sum = 0;
        
        for(const int& line : lines)
            if(line >= mid)
                sum += line/mid;

        if(sum >= need)
        {
            res = mid;
            left = mid + 1;
        }
        else
            right = mid - 1;
    }

    std::cout<<res;
}

void solve()
{
    long longest = -1;
    
    std::cin>>have>>need;
    lines.resize(have);

    for(int i =0;i<have;++i)
    {
        std::cin>>lines[i];
        longest = std::max(longest, lines[i]);
    }

    bs(longest);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();
    return 0;
}