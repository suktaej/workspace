#include <string>
#include <vector>
#include <cstdlib>
#include <limits>

int solution(std::vector<int> array, int n) 
{
    std::pair<int, int> saved(0, std::numeric_limits<int>::max());

    for(int val : array)
    {
        int temp = abs(val-n);

        if(saved.second > temp)
        {
            saved.first = val;
            saved.second = temp;
        }
        else if(saved.second == temp)
            saved.first = std::min(val,saved.first);
    }
    return saved.first;
}

int Opt(std::vector<int> array, int n) 
{
    std::pair<int, int> best(array[0],std::abs(array[0]-n));

    for (int i = 1; i < array.size(); ++i)
    {
        std::pair<int, int> val(array[i],std::abs(array[i]-n));

        if (best.second > val.second ||
            (best.second == val.second && best.first > val.first))
            best = val;
    }

    return best.first;
}