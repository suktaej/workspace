#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>

std::vector<int> SortedByProximity(std::vector<int> numlist, int n) 
{
    std::vector<std::pair<int, int>> sorted;

    for (int i = 0; i < numlist.size(); ++i)
        sorted.push_back({std::abs(numlist[i]-n),numlist[i]});

    std::sort(sorted.begin(),sorted.end());

    std::vector<int> answer;

    for (int i = 0; i < sorted.size(); ++i)
    {
        if(sorted[i].first == sorted[i+1].first)
        {
            if(sorted[i].second < sorted[i+1].second)
            {
                std::swap(sorted[i],sorted[i+1]);
                ++i;
            }
        }
    }

    for(auto num : sorted)
        answer.push_back(num.second);

    return answer;
}

bool Compare(int a, int b)
{
    return a < b;
}

void Optimize(std::vector<int> numlist, int n) 
{
    std::sort(numlist.begin(), numlist.end(),
              [&n](int a, int b) -> bool
              {
                  int da = std::abs(a - n);
                  int db = std::abs(b - n);

                  if (da != db)
                      return da < db;   // 비교 연산의 결과를 반환
                  else                  // 두 수의 거리가 같을 경우
                      return a > b;     // 내림차순 
              });
}