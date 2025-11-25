#include <iostream>
#include <vector>

int main(void)
{
    return 0;
}

std::vector<int> SumContinuousNumber(int num, int total) 
{
    std::vector<int> answer;

    int start = (total - num * (num - 1) / 2) / num;

    for(int i=0;i<num;++i)
        answer.push_back(start+i);

    return answer;
}