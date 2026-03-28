#include <iostream>
#include <vector>

int n, m;
std::vector<std::vector<int>> res;

void permute(std::vector<int>& picked, std::vector<bool>& used)
{
    if (picked.size() == m)
    {
        res.push_back(picked);
        return;
    }

    for(int i=1;i<=n;++i)
    {
        if(used[i])
            continue;

        picked.push_back(i);
        used[i] = true;

        permute(picked, used);

        picked.pop_back();
        used[i] = false;
    }
}

void combine(int start, std::vector<int>& picked)
{
    if (picked.size() == m)
    {
        res.push_back(picked);
        return;
    }

    for(int i = start; i <= n; ++i)
    {
        picked.push_back(i);

        combine(i + 1, picked);

        picked.pop_back();
    }
}

int main()
{
    std::cin>>n>>m;
    res.reserve(n);

    std::vector<bool> used(n+1, false);
    std::vector<int> arr;
    // permute(arr,used);
    combine(1,arr);

    for(const auto& p : res)
    {
        for (int i = 0; i < m; ++i)
            std::cout<<p[i]<<' ';

        std::cout<<'\n';
    }

    return 0;
}