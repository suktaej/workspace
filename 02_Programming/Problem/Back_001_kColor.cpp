#include <iostream>
#include <vector>

int V;  // 노드의 수
std::vector<std::vector<int>> graph;
std::vector<int> color;

// 현재 노드(v)에 색(c)을 칠할 수 있는지 확인
bool isSafe(int v, int c)
{
    for (int i = 0; i < V; ++i)
        // 인접노드가 현재 칠하려는 색과 같다면 
        if (graph[v][i] &&
            c == color[i])
            return false;

    return true;
}

bool graphColoring(int v, int m)
{
    // base case : 모든 색을 칠했다면 종료
    if (v == V)
        return true;

    // 1부터 m(4)까지의 색을 하나씩 시도
    // 0은 색이 없음
    for(int c = 1; c <= m; ++c)
    {
        if(isSafe(v,c))
        {
            // 색칠
            color[v] = c;

            // 다음노드 진행
            if(graphColoring(v+1,m))
                return true;

            // 실패 시 색을 지움
            color[v] = 0;
        }
    }

    return false;
}

int main() 
{
    // 예제 그래프 (인접 행렬 방식)
    // 0-1, 0-2, 0-3, 1-2, 2-3 연결된 그래프
    V = 4;
    graph = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}
    };

    color.resize(V, 0);

    int m = 4;

    if (graphColoring(0, m)) 
    {
        std::cout << "색칠 성공! 각 노드의 색상:" << std::endl;
        
        for (int i = 0; i < V; i++) 
            std::cout << i << "번 노드: 색 " << color[i] << std::endl;
        
    } 
    else 
        std::cout << "4가지 색으로는 칠할 수 없습니다." << std::endl;

    return 0;
}