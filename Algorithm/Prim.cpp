#include "GraphInput.cpp"

void Prim(const int& start)
{
    std::priority_queue<edgeInfo, std::vector<edgeInfo>, std::greater<>> minHeap; // MinHeap
    std::vector<bool> visited(gVertexCount + 1, false);

    // start node 초기화
    minHeap.push({0, start});
    visited[start] = true;
    
    // start의 adjacent node들을 priority_queue에 삽입
    for(const auto& next: adj[start])
        minHeap.push({next.first, next.second});    // {weight, dest}

    while(!minHeap.empty())
    {
        auto [curWeight, curDest] = minHeap.top();
        minHeap.pop();

        if(visited[curDest])
            continue;

        visited[curDest] = true;
        std::cout << curDest << " (weight: " << curWeight << ")\n";

        for(const auto& next : adj[curDest])
        {
            auto [nextWeight, nextDest] = next;

            if(visited[nextDest])
                continue;

            minHeap.push({nextWeight, nextDest});
        }
    }
}

int main()
{
    FileInput();
    Prim(1);
    return 0;
}