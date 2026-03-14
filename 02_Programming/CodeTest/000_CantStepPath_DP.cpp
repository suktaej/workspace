#include <vector>
#include <array>
#include <limits>
#include <cstdlib>

const std::array<int,7> height = {8, 6, 9, 2, 1, 7, 3};
const std::array<bool,7> blocked = {false, false, true, false, false, true, false};
constexpr int INF = std::numeric_limits<int>::max();
constexpr int STEP = 3;
constexpr int SIZE = height.size();

std::vector<int> memo(SIZE,-1);

int DFS(int pos)
{
    if(pos == SIZE-1)
        return 0;

    if (memo[pos] != -1)
        return memo[pos];

    int res = INF;
    
    for(int i=1;i<=STEP;++i)
    {
        int nextPos = pos + i;

        if (nextPos >= SIZE)
            continue;
        
            if(true == blocked[pos+i])
            continue;

        int cost = DFS(nextPos) + std::abs(height[pos] - height[nextPos]);
        res = std::min(res,cost);
    }

    memo[pos] = res;
    return memo[pos];
}