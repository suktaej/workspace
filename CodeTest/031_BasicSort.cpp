#include <string>
#include <vector>
#include <algorithm>

std::vector<int> solution(std::vector<int> emergency) 
{
    int size = emergency.size();
    std::vector<std::pair<int,int>> seq;

    seq.reserve(size);

    for (int i = 0; i < size; ++i)
        seq.emplace_back(emergency[i], i);

    std::sort(seq.begin(), seq.end(),
              [](auto &a, auto &b)
              {
                  return a.first > b.first;
              });

    std::vector<int> answer(size);

    for (int i = 0; i < size; ++i)
        answer[seq[i].second] = i + 1;

    return answer;
}