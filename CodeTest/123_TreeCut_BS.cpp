#include <vector>
#include <algorithm>
#include <iostream>

int n, m;
int tallest = 0;
std::vector<int> trees;

void bs()
{
    int left = 0;
    int right = tallest;
    long long res = 0;
    
    while(left <= right)
    {
        int mid = left + (right - left) / 2;
        long long sum = 0;
        
        for (const int &tree : trees)
            if (tree > mid)
                sum += tree - mid;

        if (sum >= m)
        {
            res = mid;
            left = mid + 1;
        }
        else
            right = mid - 1;
    }

    std::cout<<res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    std::cin>>n>>m;
    trees.resize(n);

    for(int i=0;i<n;++i)
    {
        std::cin>>trees[i];
        tallest = std::max(tallest,trees[i]);
    }

    bs();

    return 0;
}