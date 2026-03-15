#include <iostream>
#include <queue>

void solve()
{
    int N;
    std::priority_queue<int, std::vector<int>, std::greater<>> pq;

    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cin>>N;

    while(N--)
    {
        int n;
        std::cin>>n;

        if(n == 0)
        {
            if (pq.empty())
            {
                std::cout << "0\n";
                continue;
            }

            std::cout<<pq.top()<<'\n';
            pq.pop();
        }
        else
            pq.push(n);
    }
}

int main()
{
    solve();
    return 0;
}