#include <iostream>
#include <algorithm>
#include <deque>
#include <queue>

int testCase;
int pages;
std::pair<int,int> target;
std::deque<std::pair<int,int>> q;

void search()
{
    int cnt = 0;

    while(!q.empty())
    {
        int s = q.size();
        std::pair<int,int> cur = q.front(); // priority, position
            
        ++cnt;
        
        for (int i = 0; i < s; ++i)
            if(cur.first < q[i].first)
                cur = q[i];

        if (cur == target)
            break;

        while (!q.empty())
        {
            if (q.front() == cur)
            {
                q.pop_front();
                break;
            }

            std::pair<int,int> temp = q.front();
            q.push_back(temp);
            q.pop_front();
        }
    }
    
    std::cout<<cnt<<'\n';
}

void usingPq()
{
    int cnt = 0;
    std::priority_queue<int> pq;

    for(const auto& p : q)
        pq.push(p.first);

    while(!q.empty())
    {
        std::pair<int,int> cur = q.front();
        q.pop_front();

        if(cur.first == pq.top())
        {
            cnt++;
            pq.pop();

            if(cur.second == target.second)
            {
                std::cout<<cnt<<'\n';
                return;
            }
        }
        else
            q.push_back(cur);
    }
}

void solve()
{
    std::cin>>testCase;

    for(int i=0;i<testCase;++i)
    {
        auto& [pri, pos] = target;
        std::cin>>pages>>pos;
        q.clear();
        
        for(int j=0;j<pages;++j)
        {
            int temp;
            std::cin>>temp;
            q.push_back({temp,j});
        }
        pri = q[pos].first;

        search();
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    solve();

    return 0;
}