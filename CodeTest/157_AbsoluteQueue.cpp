#include <iostream>
#include <queue>
#include <algorithm>

struct compare
{
    bool operator()(int a, int b)
    {
        if(std::abs(a) == std::abs(b))
            return a > b;

        return std::abs(a) > std::abs(b);
    }
};

int main()
{
    int n;
    // std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<>> minHeap;
    std::priority_queue<int, std::vector<int>, compare> minHeap;

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cin>>n;

    for(int i =0; i< n;++i)
    {
        int m;
        std::cin>>m;

        if(m == 0)
        {
            if (minHeap.empty())
            {
                std::cout << 0 << '\n';
                continue;
            }

            // std::cout<<minHeap.top().second<<'\n';
            std::cout<<minHeap.top()<<'\n';
            minHeap.pop();
        }
        else
            // std::pair<int,int> node = std::make_pair(std::abs(m),m);
            minHeap.push(m);
    }
}