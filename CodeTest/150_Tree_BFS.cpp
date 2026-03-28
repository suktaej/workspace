#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

std::vector<std::vector<int>> edges;
std::vector<int> parents;

void bfs(int start)
{
    std::queue<int> q;
    q.push(start);

    while(!q.empty())
    {
        int cur = q.front();
        q.pop();

        for(int next : edges[cur])
        {
            if(parents[next]==-1)
            {
                q.push(next);
                parents[next] = cur;
            }
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin>>n;

    edges.resize(n+1);
    parents.resize(n+1,-1);

    for(int i=0;i<n-1;++i)
    {
        int f, s;
        std::cin>>f>>s;
        edges[f].push_back(s);
        edges[s].push_back(f);
    }

    bfs(1);

    for(int i=2;i<=n;++i)
        std::cout<<parents[i]<<'\n';

    return 0;
}