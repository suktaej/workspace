#include <iostream>
#include <vector>

// 전방 선언
void PerfectMatching(int count,
                     int pairSize,
                     std::vector<std::vector<int>> &current,
                     std::vector<bool> &used,
                     std::vector<std::vector<std::vector<int>>> &result);

void onComplete(std::vector<int> &temp,
                int count,
                int pairSize,
                std::vector<std::vector<int>> &current,
                std::vector<bool> &used,
                std::vector<std::vector<std::vector<int>>> &result)
{
    // 조합 완성 시 수행할 작업
    for(int x : temp)
        used[x] = true;

    current.push_back(temp);
    PerfectMatching(count, pairSize, current, used, result);
    current.pop_back();

    for(int x : temp)
        used[x] = false;
}

// 조합 생성 함수
void generateCombinations(int count,
                          int pairSize,
                          int start,
                          int depth,
                          std::vector<int> &temp,
                          std::vector<bool> &used,
                          std::vector<std::vector<int>> &current,
                          std::vector<std::vector<std::vector<int>>> &result)
{
    if(depth == pairSize - 1)
    {
        onComplete(temp, count, pairSize, current, used, result);
        return;
    }

    for(int i = start; i < count; ++i)
    {
        if(!used[i])
        {
            temp.push_back(i);
            generateCombinations(count, pairSize, i + 1, depth + 1, temp, used, current, result);
            temp.pop_back();
        }
    }
}

// PerfectMatching 재귀
void PerfectMatching(int count,
                     int pairSize,
                     std::vector<std::vector<int>> &current,
                     std::vector<bool> &used,
                     std::vector<std::vector<std::vector<int>>> &result)
{
    int first = -1;

    for(int i = 0; i < count; ++i)
    {
        if(!used[i])
        {
            first = i;
            used[i] = true;
            break;
        }
    }

    if(first == -1)
    {
        result.push_back(current);
        return;
    }

    std::vector<int> temp;
    temp.push_back(first);

    generateCombinations(count, pairSize, first + 1, 0, temp, used, current, result);

    used[first] = false;
}

int main()
{
    int n = 4;
    int pairSize = 2;

    std::vector<bool> used(n, false);
    std::vector<std::vector<int>> current;
    std::vector<std::vector<std::vector<int>>> result;

    PerfectMatching(n, pairSize, current, used, result);

    for(const auto &grouping : result)
    {
        for(const auto &group : grouping)
        {
            std::cout << "(";
            for(int i=0;i<group.size();++i)
            {
                std::cout << group[i];
                if(i+1 < group.size()) std::cout << ",";
            }
            std::cout << ") ";
        }
        std::cout << "\n";
    }
}
