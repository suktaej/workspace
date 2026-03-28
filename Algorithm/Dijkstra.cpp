#include "GraphInput.cpp"
#include <stack>

bool Dijkstra(const int& start, const int& goal)
{
    std::priority_queue<edgeInfo, std::vector<edgeInfo>, std::greater<>> minHeap;
    std::vector<int> accDist(gVertexCount + 1, INTMAX);
    std::vector<int> parent(gVertexCount + 1, 0);
    std::stack<int> path;

    accDist[start] = 0;
    minHeap.push({accDist[start], start});

    while(!minHeap.empty())
    {
        auto [curDist, curNode] = minHeap.top();
        minHeap.pop();

        if(curNode == goal)
            break;

        if(curDist > accDist[curNode])
            continue;

        for(const edgeInfo& next : adj[curNode])
        {
            auto [nextDist, nextNode] = next;

            if (accDist[curNode] != INTMAX && 
                accDist[curNode] + nextDist < accDist[nextNode])
                {
                    accDist[nextNode] = accDist[curNode] + nextDist;
                    parent[nextNode] = curNode;
                    minHeap.push({accDist[nextNode], nextNode});
                }
        }
    }

    if (accDist[goal] == INTMAX)
        return false;

    int temp = goal;

    while (temp != 0)
    {
        path.push(temp);
        temp = parent[temp];
    }

    while(!path.empty())
    {
        std::cout<<path.top()<<(path.size() > 1 ? "->" : "");
        path.pop();
    }

    return true;
}

int main()
{
    FileInput();
    Dijkstra(1,5);

    return 0;
}