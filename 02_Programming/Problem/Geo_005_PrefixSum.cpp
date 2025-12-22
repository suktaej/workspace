#include <vector>
#include <array>

std::vector<int> arr = { 2, 4, 6, 8, 10, 12 };
int size = arr.size();

void PrefixSum()
{
    std::vector<int> prefix(size, 0);

    // 누적합 초기 세팅
    prefix[0] = arr[0];
    for (int i = 1; i < size; i++)
    {
        prefix[i] = prefix[i - 1] + arr[i];
    }

    // 구간 [2, 4]의 합 : 6 + 8 + 10 = 24
    int result = prefix[4] - prefix[2];
}

void PrefixDiff(int country, std::vector<std::vector<int>> snow)
{
    std::vector<int> prefix(country + 1, 0);
    int date = snow.size();

    for(auto& it : snow)
    {
        int begin = it[0];
        int end = it[1];
        int height = it[2];

        prefix[begin] += height;
        prefix[end+1] -= height;
    }

    std::vector<int> acc(country, 0);
    acc[0] = prefix[0];

    for (int i = 1; i < country; ++i)
        acc[i] = acc[i - 1] + prefix[i];
}

constexpr int station = 4;
const std::array<int, station - 1> dist = {8, 6, 9};
const std::array<int, 6> travel = {2, 1, 3, 2, 3, 4};
std::vector<int> distPrefix(station, 0);

int GetDist(int a, int b)
{
    if(a==b)
        return 0;

    int from = std::min(a,b);
    int to = std::max(a,b);

    /*
    int sum = 0;
    for(int i = from; i<to; ++i)
        sum += dist[i - 1];

    return sum;
    */

    return distPrefix[to - 1] - distPrefix[from - 1];
}

void MoveTrain()
{
    for (int i = 1; i < station; ++i)
        distPrefix[i] = distPrefix[i - 1] + dist[i - 1];

    int date = travel.size();
    std::vector<int> prefix(date,0);

    for (int i = 1; i < date; ++i)
    {
        int prevStation = travel[i-1];
        int currentStation = travel[i];
        int moveDist = GetDist(prevStation,currentStation);

        prefix[i] = prefix[i-1]+moveDist;
    }
}
