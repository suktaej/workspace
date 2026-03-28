#include <vector>

constexpr int MAX = 16;
int n;
std::vector<std::vector<int>> adj;

int hamilton()
{
    // dp[mask][i] : mask에 해당하는 노드들을 방문했고, 현재 i번 노드에 있을 때 해밀턴 경로 가능 여부
    bool dp[1 << MAX][MAX];

    // 1. 초기 상태 (각 노드에서 시작하는 경우)
    for (int i = 0; i < n; i++)
        dp[1 << i][i] = true;

    // 2. 비트마스크 반복문 (가중치 계산 대신 연결성만 확인)
    for (int mask = 1; mask < (1 << n); mask++)
    {
        for (int curr = 0; curr < n; curr++)
        {
            if (!(mask & (1 << curr)))
                continue; // 현재 mask에 curr가 포함 안 되어 있으면 패스

            if (!dp[mask][curr])
                continue; // 현재 상태가 불가능하면 패스

            // 다음 노드 탐색
            for (int next = 0; next < n; next++)
            {
                    // 방문 안 했고, 간선이 있다면 다음 상태 가능
                if (!(mask & (1 << next)) && adj[curr][next])
                    dp[mask | (1 << next)][next] = true; 
            }
        }
    }

// 3. 결과 확인
// dp[(1 << n) - 1][i] 중 하나라도 true이면 해밀턴 경로 존재
}

int main()
{
    return 0;
}