#include <iostream>
#include <functional>
#include <vector>

// 0번부터 순서대로 나열된 수 중 count만큼의 조합
void CombinationPick(int count, std::vector<int>& picked, int toPick, std::vector<std::vector<int>>& result)
{
    // Base case
    if (0 == toPick)
    {
        result.push_back(picked);
        return;
    }

    // 가장 작은 숫자
    int smallest = picked.empty() ? 0 : picked.back() + 1;

    // 삽입할 원소 선택
    for(int next = smallest; next < count; ++next)
    {
        picked.push_back(next);
        CombinationPick(count, picked, toPick - 1, result);
        picked.pop_back();
    }
}

void PermutationPick(int count, std::vector<int>& picked, int toPick, std::vector<bool>& used, std::vector<std::vector<int>>& result)
{
    if(0 == toPick)
    {
        result.push_back(picked);
        return;
    }

    for(int i = 0; i< count; ++i)
    {
        if(used[i])
            continue;
        
        picked.push_back(i);
        used[i] = true;
        PermutationPick(count, picked, toPick-1, used, result);
        picked.pop_back();
        used[i] = false;

    }
}

void PerfectMatching(int count,
                     int pairSize,
                     std::vector<std::vector<int>> &current,
                     std::vector<bool> &used,
                     std::vector<std::vector<std::vector<int>>> &result)
{
    // base case
    // 모든 element가 사용되었다면 결과추가
    /*
    // count만큼 중복탐색하므로 순회를 1회로 최적화
    bool done = true;

    for (int i = 0; i < count; ++i)
    {
        if(!used[i])
        {
            done = false;
            break;
        }
    }

    if(done)
    {
        result.push_back(current);
        return;
    }

    // 사용되지 않은 element 선택
    int first = -1;

    for (int i = 0; i < count; ++i)
    {
        if(!used[i])
        {
            first = i;
            used[i] = true;
            break;
        }
    }
    */

    int first = -1;

    for (int i = 0; i < count; ++i)
    {
        if(!used[i])
            first = i;

        used[i] = true;
        break;
    }

    if(-1 == first)
    {
        result.push_back(current);
        return;
    }

    // first와 나머지 k-1개를 묶는 combination 생성
    // pairSize가 4일 경우, temp는 ( , , , )를 채워야 함
    // 우선 가장 낮은 수인 first 삽입 (first, , , )
    std::vector<int> temp;
    temp.push_back(first);

    // recursion : 나머지 k-1개 선택
    std::function<void(int, int)> combine = [&](int start, int depth)
    {
        // 조합이 완성되었을 경우
        if (depth == pairSize - 1)
        {
            // 선택 된 k개 묶음 추가
            for(int x : temp)
                used[x] = true;
            
            current.push_back(temp);

            PerfectMatching(count, pairSize, current, used, result);
           
            current.pop_back();

            for(int x : temp)
                used[x] = false;
            
            return;
        }
        
        // 조합을 생성
        for (int i = start; i < count; ++i)
        {
            if(!used[i])
            {
                temp.push_back(i);
                combine(i + 1, depth + 1);
                temp.pop_back();
            }
        }
    };

    // lambda 함수에 first 다음 수를 삽입 (first, first+1, , )
    // 내부에서 recursion
    combine(first + 1, 0);
    // Combine이 종료되면 first를 used에서 제거
    used[first] = false;
}

void combine(int count,
             int pair,
             std::vector<int> &temp,
             std::vector<bool> &used,
             int start,
             int depth,
             std::vector<std::vector<int>> &current,
             std::vector<std::vector<std::vector<int>>> &result,
             void (*generateGroupsPtr)(int,
                                       int,
                                       std::vector<std::vector<int>> &,
                                       std::vector<std::vector<std::vector<int>>> &,
                                       std::vector<bool> &))
{
    if(depth == pair-1) 
    {
        // 선택된 k개 묶음 추가
        for(int x : temp) used[x] = true;
        current.push_back(temp);

        // generateGroups 호출
        generateGroupsPtr(count, pair, current, result, used);

        current.pop_back();
        for(int x : temp) used[x] = false;

        return;
    }

    for(int i = start; i < count; ++i) 
    {
        if(!used[i]) {
            temp.push_back(i);

            combine(count, pair, temp, used, i+1, depth+1, current, result, generateGroupsPtr);

            temp.pop_back();
        }
    }
}

void ShowResult(std::vector<std::vector<int>> result, int count)
{
    for(auto vec : result)
    {
        for(int i=0;i<count;++i)
            std::cout<< vec[i] <<" ";
        
        std::cout<<"\n";
    }
}

int Permutation(int n, int r)
{
    int result = 1;

    for(int i =0; i< r; ++i)
        result *= n - i;

    return result;
}

int Combination(int n, int r)
{
    int p = Permutation(n,r);
    int rFact = 1;

    for(int i=2;i<=r;++i)
        rFact *= i;

    return p / rFact;
}

int main(void)
{
    constexpr int maxNum = 8;
    constexpr int maxCount = 4;
    std::vector<std::vector<int>> result;
    std::vector<bool> used(maxNum,false);
    std::vector<int> picked;

    std::vector<std::vector<std::vector<int>>> matchResult;
    std::vector<std::vector<int>> current;

    // CombinationPick(maxNum,picked,maxCount,result);
    // ShowResult(result,maxCount);
    // std::cout<<"The number of result : "<<Combination(maxNum,maxCount)<<"\n";

    // PermutationPick(maxNum,picked,maxCount,used,result);
    // ShowResult(result,maxCount);
    // std::cout<<"The number of result : "<<Permutation(maxNum,maxCount)<<"\n";

    PerfectMatching(maxNum, maxCount, current, used, matchResult);

    for (auto &r : matchResult)
    {
        for (auto &group : r)
        {
            std::cout << "(";
            for (size_t i = 0; i < group.size(); ++i)
            {
                std::cout << group[i];
                if (i + 1 < group.size())
                    std::cout << ",";
            }
            std::cout << ") ";
        }
        std::cout << "\n";
    }

    return 0;
}