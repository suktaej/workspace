#include <vector>
#include <array>
#include <algorithm>
#include <iostream>

constexpr int MAX = 1001;

std::array<std::vector<int>,MAX> gAdj{};
std::array<int,MAX> gOccupied{};
std::array<bool,MAX> gVisited{};

int n, m; // n: 학생 수, m: 자리 수

bool DFS(int u)
{
    for(int v : gAdj[u])
    {
        if(gVisited[v])
            continue;
        
        gVisited[v] = true;

        if (gOccupied[v] == 0 ||
            DFS(gOccupied[v]))
            {
                gOccupied[v] = u;
                return true;
            }
    }

    return false;
}

void Input()
{
    int k;    // 간선의 수 (학생들이 제출한 선호 자리 총합)

    std::cin >> n >> m >> k;

    for (int i = 0; i < k; i++) 
    {
        int u, v;
        std::cin >> u >> v;
        gAdj[u].push_back(v); // 학생 u가 좌석 v를 선호함
    }
}

int main() 
{
    Input();
    int match_count = 0;
    
    // 모든 학생에 대해 한 명씩 매칭 시도
    for (int i = 1; i <= n; i++) 
    {
        // 매 학생마다 visited 배열 초기화
        // visited[MAX] 일 경우
        // std::fill(visited, visited + MAX, false);

        gVisited.fill(false);
        // or std::fill(gVisited.begin(), gVisited.end(), false);
        // or std::fill(gVisited.data(), gVisited.data() + gVisited.size(), false);
        
        if (DFS(i)) 
            ++match_count;
    }

    std::cout << "최대로 자리에 앉을 수 있는 학생 수: " << match_count << std::endl;

    // 누가 어디에 앉았는지 출력
    for (int i = 1; i <= m; i++) 
        if (gOccupied[i] != 0) 
            std::cout << i << "번 좌석: " << gOccupied[i] << "번 학생" << std::endl;

    return 0;
}