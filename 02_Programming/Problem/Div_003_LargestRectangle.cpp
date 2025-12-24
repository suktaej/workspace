#include <vector>
#include <iostream>
#include <array>
#include <algorithm>

std::array<int, 7> f1 = {7, 1, 5, 9, 6, 7, 3};
std::array<int, 7> f2 = {1, 4, 4, 4, 4, 1, 1};
std::array<int, 4> f3 = {1, 8, 2, 2};

int Brute(const std::vector<int>& fence)
{
    int res = 0;
    int n = fence.size();

    for(int left = 0; left < n ; ++left)
    {
        int minHeight = fence[left];
        for(int right = left; right < n; ++right)
        {
            minHeight = std::min(minHeight, fence[right]);
            res = std::max(res, (right - left + 1) * minHeight);
        }
    }

    return res;
}

std::vector<int> fence(f1.begin(),f1.end());

int Opt(int left, int right)
{
    // base case 
    if(left == right)
        return fence[left];

    int mid = (right + left) / 2;
    int lo = mid;
    int hi = mid + 1;

    // 중간 경계를 넘지 않는 구역에서의 최대값
    int res = std::max(Opt(left, lo), Opt(hi, right));

    // 경계를 걸치는 직사각형 탐색 시작
    int height = std::min(fence[lo], fence[hi]);
    res = std::max(res, height * 2);

    while(left < lo || right > hi)
    {
        if (hi < right &&
            (lo == left || fence[lo - 1] < fence[hi + 1]))
        {
            ++hi;
            height = std::min(height, fence[hi]);
        }
        // else if (lo > left && (hi == right || fence[lo - 1] >= fence[hi + 1]))
        else
        {
            --lo;
            height = std::min(height, fence[lo]);
        }

        res = std::max(res, height * (hi - lo + 1));
    }

    return res;
}

int main()
{
    // std::cout<<Brute(fence);
    std::cout<<Opt(0,fence.size()-1);

    return 0;
}