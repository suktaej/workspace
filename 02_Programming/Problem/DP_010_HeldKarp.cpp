#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <array>

constexpr int INF = std::numeric_limits<int>::max();
constexpr int SIZE = 16;    // 방문 도시 수
int n;
std::array<std::array<int,SIZE>,SIZE> dist; // 최대 도시 수
std::array<std::array<int,1<<SIZE>,SIZE> dp;    // dp[방문상태][현재위치]

/**
 * @param mask: 현재까지 방문한 도시들을 비트로 표시 (예: 1011이면 0, 1, 3번 도시 방문)
 * @param curr: 현재 위치한 도시 번호
 * @return: 현재 상태에서 모든 도시를 다 돌고 0번(시작점)으로 돌아가는 최소 비용
 */

 int TSP(int mask, int cur)
 {
    // base case : 모든 도시를 방문한 경우(mask bit가 모두 1일 때)
     if (mask == (1 << n) - 1)
     {
         if (dist[cur][0] == 0) // 시작점으로 돌아가지 못하면 경로없음
             return INF;

         return dist[cur][0];   // 현재 위치에서 시작점으로 돌아가는 비용 반환
     }

     // 이미 계산한 상태라면 값을 반환(Memorization)
     if(dp[mask][cur]!= -1)
        return dp[mask][cur];

    // 초기값 설정
    dp[mask][cur] = INF;

    // 도시순회(DFS)
    for(int next = 0; next < n; ++next)
    {
        if (mask & (1 << next))
            continue;

        if (dist[cur][next] == 0)
            continue;

        // 다음 상태 호출
        int res = TSP(mask | (1<<next), next);

        // 최솟값 갱신
        dp[mask][cur] = std::min(dp[mask][cur], res + dist[cur][next]);
    }

    return dp[mask][cur];
 }

 void input()
 {
    std::cin >> n;
    for (int i = 0; i < n; ++i) 
        for (int j = 0; j < n; ++j) 
            std::cin >> dist[i][j];
    
    // DP 테이블을 -1로 초기화 
    for (int i = 0; i < (1 << n); ++i) 
        for (int j = 0; j < n; ++j) 
            dp[i][j] = -1;
 }

 int main()
 {
    input();
    int res = TSP(1 << 0, 0);

    if(res >= INF)
        std::cout<<"No path";
    else
        std::cout<<res;

    return 0;
 }