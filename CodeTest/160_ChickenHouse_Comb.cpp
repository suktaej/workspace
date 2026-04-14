#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

int n, m;
std::vector<std::pair<int,int>> chick;
std::vector<std::pair<int,int>> picked;
std::vector<std::pair<int,int>> house;
int res = 1e9;

void calc()
{
    int totalDist = 0;

    for(const auto& i : house)
    {
        int minDist = 1e9;

        for(const auto& j : picked)
        {
            int dist = std::abs(i.first - j.first) + std::abs(i.second - j.second);
            minDist = std::min(dist,minDist);
        }

        totalDist += minDist;
    }

    res = std::min(totalDist,res);
}

void combine(int next)
{
    if (picked.size() == m)
    {
        calc();
        return;
    }

    for (int i = next; i < chick.size(); ++i)
    {
        std::pair<int,int> pos = chick[i];

        picked.push_back(pos);
        combine(i+1);
        picked.pop_back();
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin>>n>>m;

    chick.reserve(n*n);
    house.reserve(n*n);
    picked.reserve(m);
    // house.assign(n,std::vector<int>(n,0));

    for(int i =0;i<n;++i)
    {
        for(int j =0;j<n;++j)
        {
            int k;
            std::cin >> k;

            if (k == 1)
                house.push_back({i,j});

            if (k == 2)
                chick.push_back({i,j});
        }
    }

    combine(0);
    std::cout<<res;

    return 0;
}