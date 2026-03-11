#include <vector>
#include <array>
#include <cmath>
#include <limits>

std::array<std::pair<int,int>,7> points = {{{1,1},{2,6},{5,8},{3,6},{8,2},{6,1},{7,3}}};
constexpr float INF = std::numeric_limits<float>::max();

float Dist(const std::pair<int,int>& a,const std::pair<int,int>& b)
{
    float x = a.first - b.first;
    float y = a.second - b.second;
    // return std::sqrt(x*x+y*y);   // 거리비교이므로 sqrt연산 불필요
    return x*x + y*y;
}

std::pair<std::pair<int,int>, std::pair<int,int>> FindClosestPoints()
{
    int size = points.size();
    float minDist = INF;
    std::pair<int,int> res1;
    std::pair<int,int> res2;

    for (int i = 0; i < size - 1; ++i)
    {
        for (int j = i + 1; j < size; ++j)
        {
            float temp = Dist(points[i],points[j]);

            if(temp < minDist)
            {
                minDist = temp;
                res1 = points[i];
                res2 = points[j];
            }
        }
    }

    return {res1,res2};
}
