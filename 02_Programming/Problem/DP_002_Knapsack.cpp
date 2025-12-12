#include <vector>

const std::vector<std::pair<int, int>> knapsack;    // value, weight
constexpr int maxWeight;

int DP()
{
    int size = knapsack.size();
    std::vector<std::vector<int>> dp(size + 1, std::vector<int>(maxWeight + 1, 0));

    // 0번지는 미선택
    for (int i = 1; i <= size; ++i)
    {
        int value = knapsack[i-1].first;
        int weight = knapsack[i-1].second;

        // w는 적재가능한 배낭의 최대 무게
        for (int w = 0; w <= maxWeight; ++w)
        {
            // 미선택 시
            dp[i][w] = dp[i-1][w];

            // 선택 시
            if(w >= weight)
                dp[i][w] = std::max(dp[i][w], dp[i - 1][w - weight] + value);
        }
    }

    return dp[size][maxWeight];
}


int Rec(int itemIdx, int accValue, int accWeight)
{
    if(itemIdx == knapsack.size()-1)
        return accValue;

    int noTake = Rec(itemIdx+1, accValue, accWeight);

    int take = 0;

    if(accWeight + knapsack[itemIdx].second <= maxWeight)
        take = Rec(itemIdx +1 , accWeight+knapsack[itemIdx].second, accValue+=knapsack[itemIdx].first);
    
    return std::max(noTake,take);
}

int main(void)
{

    return 0;
}