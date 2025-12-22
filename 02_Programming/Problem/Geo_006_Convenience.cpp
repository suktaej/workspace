#include <array>
#include <vector>

constexpr int person = 7;
constexpr int closingTime = 10;
constexpr int openingTime = 0;
const std::array<std::pair<int, int>, person> workHours = {{{0, 3}, {2, 4}, {1, 3}, {0, 3}, {5, 6}, {5, 6}, {5, 6}}};

void WorkingSteps()
{
    std::vector<int> diff(closingTime + 1, 0);
        
    for(auto& it : workHours)
    {
        diff[it.first] += 1;
        diff[it.second] -= 1;
    }

    std::vector<int> working(closingTime, 0);
    working[0] = diff[0];

    for (int i = 1; i < closingTime; ++i)
        working[i] = working[i - 1] + diff[i];
}