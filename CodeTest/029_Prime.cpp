#include <string>
#include <vector>
#include <algorithm>

std::vector<int> solution(int n) 
{
    std::vector<int> answer;
    int prime = 2;
   
    while(n > 1)
    {
        if (0 == n % prime)
        {
            n /= prime;
            answer.push_back(prime);
        }
        else
            ++prime;
    }

    std::sort(answer.begin(),answer.end());
    answer.erase(std::unique(answer.begin(),answer.end()),answer.end());

    return answer;
}