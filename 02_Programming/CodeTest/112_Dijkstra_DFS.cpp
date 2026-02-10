#include <iostream>
#include <vector>

int n, e;
std::vector<std::vector<std::pair<int,int>>> gNode;

void input()
{
    std::cin>>n>>e;
    gNode.resize(n);

    for(int i=0;i<e;++i)
    {
        int u, v, w;
        std::cin>>u>>v>>w;
        gNode[u].push_back({v, w});
        gNode[v].push_back({u, w});
    }
}

int main()
{
    input();
    return 0;
}