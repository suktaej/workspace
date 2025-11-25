#include <iostream>
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
    constexpr int maxNum = 7;
    constexpr int maxCount = 4;
    std::vector<std::vector<int>> result;
    std::vector<bool> used(maxNum,false);
    std::vector<int> picked;

    //CombinationPick(maxNum,picked,maxCount,result);
    PermutationPick(maxNum,picked,maxCount,used,result);
    ShowResult(result,maxCount);
    std::cout<<"The number of result : "<<Permutation(maxNum,maxCount)<<"\n";

    return 0;
}