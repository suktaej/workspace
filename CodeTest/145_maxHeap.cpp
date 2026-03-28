#include <iostream>
#include <queue>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::priority_queue<int> pq;
    std::cin>>n;
    for(int i=0;i<n;++i)
    {
        int temp;
        std::cin>>temp;
        if (temp == 0)
        {
            if(pq.empty())
                std::cout<<0<<'\n';
            else
            {
                std::cout << pq.top()<<'\n';
                pq.pop();
            }
        }
        else
            pq.push(temp);
    }

    return 0;
}