#include <iostream>
#include <vector>

constexpr int COLOR_COUNT = 4;
int n;
std::vector<std::vector<int>> adj;
std::vector<int> colorNodes;

int input()
{
    std::cin>> n;
    adj.reserve(n);
    colorNodes.resize(n);

    for (int i = 0; i < n; ++i)
    {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
    }
}

bool canPlace(int node, int color)
{
    for(int neigh : adj[node])
        if(colorNodes[neigh] == color)
            return false;

    return true;
}

bool colorSolve(int node)
{
    if(node == n)
        return true;

    for (int i = 1; i <= COLOR_COUNT; ++i)
    {
        if(canPlace(node,i))
        {
            colorNodes[node] = i;

            if(colorSolve(node+1))
                return true;

            colorNodes[node] = 0;
        }
    }

    return false;
}

int main()
{
    input();
    colorSolve(0);

    return 0;
}