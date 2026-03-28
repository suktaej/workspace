#include <vector>
#include <iostream>

int DP(int stepCount, int stepRange)
{
    std::vector<int> acc(stepCount + 1, 0);
    acc[0] = 1;

    for (int i = 1; i <= stepCount; ++i)
    {
        for (int j = 1; j <= stepRange; ++j)
        {
            if (i - j < 0)
                break;

            acc[i] += acc[i - j];
        }
    }

    return acc[stepCount];
}

int main()
{
    std::cout<<DP(6,2);
    return 0;
}