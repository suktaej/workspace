#include <iostream>
#include <vector>

int n = 10;
bool arePairs[10][10];


int CountPairings(bool taken[10])
{
    // 가장 번호가 빠른 인원
    int firstFree = -1;

    for (int i = 0; i < n; ++i)
    {
        if(!taken[i])
        {
            firstFree = i;
            break;
        }
    }
    // Base case
    // 모두 짝을 찾았으니 종료
    if(firstFree == -1)
        return 1;

    // 가장 번호가 빠른 인원이 생성되었다면 짝을 찾음
    int ret = 0;

    for(int pairWith = firstFree+1; pairWith < n; ++pairWith)
    {
        if(!taken[pairWith] && arePairs[firstFree][pairWith])
        {
            taken[firstFree] = true;
            taken[pairWith] = true;
      
            ret += CountPairings(taken);
        
            taken[firstFree] = false;
            taken[pairWith] = false;
        }
    }
    
    return ret;
}

int main(void)
{
    int person = 10;
    int pair = 2;
    std::vector<std::vector<int>> res;
    std::vector<int> pick;
    std::vector<bool> used(person,false);

    for(auto vec : res)
    {
        for(int num : vec)
            std::cout<<num<<" ";
        std::cout<<"\n";
    }

    return 0;
}