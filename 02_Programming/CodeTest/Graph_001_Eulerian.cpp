#include <iostream>
#include <vector>

int n;
std::vector<std::vector<int>> graph;
std::vector<bool> visited;

bool DFS(int cur)
{
    // init
    visited[cur] = true;

    // loop
    for(const int next : graph[cur])
    {
        if(visited[next])
            continue;

        DFS(next);
    }
}

int nodeCounting(int cur)
{
    // init
    visited[cur] = true;
    int count = 1;

    // loop
    for(const int next : graph[cur])
    {
        if(visited[next])
            continue;

        count += nodeCounting(next);
    }

    return count;
}

bool isAllConnectedByVisit()
{
    if (n == 0)
        return true;
    
    DFS(0);

    for (int i = 0; i < n; ++i) 
        if (!visited[i]) 
            return false; 
        
    return true; 
}

bool isAllConnectedByCount()
{
    // 만약 노드가 없으면 true
    if (n == 0) 
        return true;

    // 간선이 있는 첫 번째 노드에서 DFS를 시작
    int startNode = -1;

    for (int i = 0; i < n; i++)
    {
        if(graph[i].size() > 0) 
        {
            startNode = i;
            break;
        }
    }
    
    // 간선이 하나도 없는 그래프라면 오일러 경로가 있다고 봄
    if (startNode == -1) 
        return true;

    // 간선이 있는 노드들만 다 연결되었는지 확인하려면 
    // 전체 n 대신 '간선이 있는 노드 수'와 비교
    return nodeCounting(startNode) == n; 
}

int main()
{
    if (isAllConnectedByCount()) 
    {
        int oddEdgeVertex = 0;

        for (int i = 0; i < n; ++i) 
            if (graph[i].size() % 2 != 0) 
                ++oddEdgeVertex;

        if (oddEdgeVertex == 0 || oddEdgeVertex == 2)
            std::cout << "Success";
        else
            std::cout << "Failure";
    }
    else 
        std::cout << "Failure";

    return 0;
}