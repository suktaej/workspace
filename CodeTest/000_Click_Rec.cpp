#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <limits>
#include <algorithm>

constexpr int CLOCKS = 16;
constexpr int SWITCHES = 10;
constexpr int INF = std::numeric_limits<int>::max();

const std::vector<std::vector<int>> connectedClocks = {
    {0, 1, 2},              // Switch 0
    {3, 7, 9, 11},          // Switch 1
    {4, 10, 14, 15},        // Switch 2
    {0, 4, 5, 6, 7},        // Switch 3
    {6, 7, 8, 10, 12},      // Switch 4
    {0, 2, 14, 15},         // Switch 5
    {3, 14, 15},            // Switch 6
    {4, 5, 7, 14, 15},      // Switch 7
    {1, 2, 3, 4, 5},        // Switch 8
    {3, 4, 5, 9, 13}        // Switch 9
};

bool AreAligned(const std::vector<int>& clocks)
{
    for(const int& c : clocks)
        if (c != 12)
            return false;
    
    return true;
}

void Push(std::vector<int> &clocks, int switcher)
{
    for (int clockIdx : connectedClocks[switcher])
    {
        clocks[clockIdx] +=3;

        if(clocks[clockIdx] == 15)
            clocks[clockIdx] = 3;
    }
}

int Solve(std::vector<int>& clocks,int switcher)
{
    if(switcher == SWITCHES)
        return AreAligned(clocks) ? 0 : INF;

    int res = INF;

    for(int cnt = 0; cnt < 4; ++cnt)
    {
        int temp = Solve(clocks, switcher+1);

        if (temp != INF)
            res = std::min(res, cnt + temp);
        Push(clocks,switcher);
    }

    return res;
}

int main()
{
    std::vector<int> clocks = {12, 12, 12, 3, 3, 3, 12, 12, 12, 3, 12, 12, 12, 3, 12, 12};
    std::cout << Solve(clocks, 0);

    return 0;
}