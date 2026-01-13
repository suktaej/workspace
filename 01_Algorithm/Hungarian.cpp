#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

/*
  Hungarian Algorithm (O(N^3))
  가중치가 존재하는 이분 그래프에서 최소비용 완전매칭을 탐색
  n: 행의 개수 (Workers)
  m: 열의 개수 (Jobs)
  cost: n x m 비용 행렬 (1-based)
  
  주의: n <= m 이어야 모든 행이 매칭
  n > m 이라면 행렬을 전치(transpose)

  1. 행에서 최소값을 뻴셈
  2. 열에서 최소값을 뻴셈
  3. 모든 0이 포함되도록 선을 그어 n과 같은지 확인(Covering Zeros)
  4. n보다 작다면 선이 그어지지 않은 수 중 최소값을 확인
  5-1. 선이 지나가지 않는 영역에서 값을 뻴셈
  5-2. 선이 1개만 지나가는 영역은 무시
  5-3. 선 2개가 중복되는 영역은 값을 더함
  6. 다시 최적의 0이 도출되는지 확인 후 원본 값에서 해당 좌표의 값을 확인
*/

constexpr int INF = std::numeric_limits<int>::max();

std::pair<int, std::vector<int>> Hungarian(int n, int m, const std::vector<std::vector<int>>& cost) 
{
    // Potentials(cost)
    std::vector<int> u(n + 1, 0);
    std::vector<int> v(m + 1, 0);  
    std::vector<int> p(m + 1, 0);  // p[j]는 column j와 matching된 row i를 저장
    std::vector<int> way(m + 1, 0);// 경로 역추적용

    for (int i = 1; i <= n; ++i)
    {
        p[0] = i;   // 현재 matching할 row를 임시저장 (1base이므로 빈 공간)
        int j0 = 0;

        std::vector<int> minv(m + 1, INF);  // 각 column에 도달하는 최소비용
        std::vector<bool> used(m + 1, false);   // BFS에서 방문여부

        // BFS
        do 
        {
            used[j0] = true;    // 현재 column 방문
            int i0 = p[j0];     // 현재 column j0과 매칭되어 있는 row
            int j1 = 0;
            int delta = INF;    // Potental 조정 최소치

            for (int j = 1; j <= m; ++j) 
            {
                if (!used[j]) 
                {
                    // 현재 작업자(i0)이 j번 일을 할 때의 여유비용
                    int cur = cost[i0][j] - u[i0] - v[j];
                    if (cur < minv[j])
                    {
                        minv[j] = cur;
                        way[j] = j0;    // j번 column으로 오기 위해 j0번 column을 거쳤음을 기록
                    }

                    if (minv[j] < delta)
                    {
                        delta = minv[j];    // 이번 단계에서 가장 작은 여유비용 갱신
                        j1 = j;             // j1 : 가장 유망한 다음열
                    }
                }
            }

            // Potential Update
            for (int j = 0; j <= m; ++j) 
            {
                if (used[j]) 
                {
                    u[p[j]] += delta;   // 방문한 vertex의 potental 조정
                    v[j] -= delta;
                }
                else
                    minv[j] -= delta;   // 방문하지 않은 vertex들은 delta만큼의 여유
            }

            j0 = j1;    // 다음 탐색할 열을 j1로 변경
        } while (p[j0] != 0);   // 열 j0이 아직 매칭되지 않았다면 종료

        // 경로 역추적
        do 
        {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0 != 0);
    }

    // -v[0]에 최소 비용의 합이 저장됨
    std::vector<int> match(n + 1);
    for (int j = 1; j <= m; ++j) 
        if (p[j] != 0)
            match[p[j]] = j;

    return {-v[0], match};
}

int main()
{
    int n = 3;
    int m = 3;
    std::vector<std::vector<int>> cost(n + 1, std::vector<int>(m + 1));

    cost[1] = {0, 7, 6, 2};
    cost[2] = {0, 8, 5, 4};
    cost[3] = {0, 3, 1, 5};

    auto result = Hungarian(n, m, cost);

    std::cout << "min cost: " << result.first << std::endl;

    for (int i = 1; i <= n; ++i)
        std::cout << i << " worker -> " << result.second[i] << " job" << std::endl;

    return 0;
}