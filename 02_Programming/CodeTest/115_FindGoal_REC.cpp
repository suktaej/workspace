#include <iostream>
#include <unordered_map>
#include <algorithm>

std::unordered_map<int,int> memo;
int target;

int solve(int pos)
{
    if(target >= pos)
        return target - pos;

    if(pos == 1)
        return (target == 0 ? 1 : pos - 1);

    if (memo.count(pos)) 
        return memo[pos];

    int res = 0;

    if (pos % 2 == 0)
        res = std::min(pos - target, 1 + solve(pos / 2));
    else
        res = 1 + std::min(solve(pos - 1), solve(pos + 1));
    
    memo[pos] = res;
    return res;
}

int main()
{
    int goal;
    std::cin>>target>>goal;
    std::cout<<solve(goal);
    
    return 0;
}