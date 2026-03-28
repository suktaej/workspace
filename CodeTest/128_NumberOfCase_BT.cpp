#include <iostream>
#include <vector>
#include <bits/stdc++.h>

int n, m;
std::vector<int> bundle;

// std::vector<std::vector<int>> res;

void combine(int cur)
{
    if (bundle.size() == m)
    {
        // res.push_back(bundle);
        for(const int& i : bundle)
            std::cout<<i<<' ';
        std::cout<<'\n';
        
        return;
    }

    for(int i =cur; i<= n; ++i)
    {
        bundle.push_back(i);
        // combine(i+1);
        combine(i);
        bundle.pop_back();
    }
}

void permute(std::vector<bool>& used)
{
    if (bundle.size() == m)
    {
        for(const int& i : bundle)
            std::cout<<i<<' ';
        std::cout<<'\n';
        
        return;
    }

    for(int i=1;i<=n;++i)
    {
        if(used[i])
            continue;

        bundle.push_back(i);
        // used[i] = true;

        permute(used);

        bundle.pop_back();
        // used[i] = false;
    }

}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::vector<bool> used;
    
    std::cin>>n>>m;
    bundle.reserve(m);
    used.resize(m,false);

    // combine(1);
    permute(used);

    return 0;
}