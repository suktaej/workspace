#include <iostream>
#include <vector>
#include <cstdlib>

static constexpr int gPersonCount = 10;

int CountPairings(bool taken[gPersonCount], bool pairs[][gPersonCount])
{
    // 가장 번호가 빠른 인원
    int first = -1;

    for (int i = 0; i < gPersonCount; ++i)
    {
        if(!taken[i])
        {
            first = i;
            break;
        }
    }

    // Base case
    // 모두 짝을 찾았으니 종료
    if(first == -1)
        return 1;

    // 가장 번호가 빠른 인원이 생성되었다면 짝을 찾음
    int result = 0;

    for (int i = first + 1; i < gPersonCount; ++i)
    {
        if(taken[i])
            continue;
        
        if(!pairs[first][i])
            continue;
        
        taken[first] = taken[i] = true;
        result += CountPairings(taken, pairs);
        taken[first] = taken[i] = false;
    }
    
    return result;
}

int main(void)
{
    bool arePairs[gPersonCount][gPersonCount] = {};
    bool used[gPersonCount] = {};

    srand(100);

    for(int i =0;i<gPersonCount;++i)
        for (int j = 0; j < gPersonCount; ++j)
            arePairs[i][j] = rand() % 2;

    std::cout<<CountPairings(used,arePairs);

    return 0;
}