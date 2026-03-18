#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
// #include <bits/stdc++.h>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin>>n;

    std::vector<int> values(n);
    constexpr int limCond = 4000;
    std::vector<int> cnt(2*limCond+1,0);
    double sum = 0;

    for(int i=0;i<n;++i)
    {
        std::cin>>values[i];
        sum += values[i];
        ++cnt[values[i] + limCond];
    }

    int avg = round(sum / n);
    if(avg == -0)
        avg = 0;

    int maxFreq = 0;
    for(int i =0;i<2*limCond+1;++i)
        if(cnt[i] > maxFreq)
            maxFreq = cnt[i];

    std::vector<int> modes;
    for(int i=0; i< 2*limCond+1;++i)
        if(cnt[i]==maxFreq)
            modes.push_back(i - limCond);

    int mode;
    if(modes.size() > 1)
    {
        std::sort(modes.begin(),modes.end());
        mode = modes[1];
    }
    else
        mode = modes[0];

    std::sort(values.begin(),values.end());
    int mid = values[n/2];
    int range = values.back() - values.front();

    std::cout<<avg<<'\n'<<mid<<'\n'<<mode<<'\n'<<range;

    return 0;
}