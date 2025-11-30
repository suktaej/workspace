#include <string>
#include <vector>
#include <algorithm>

int UsingFor(std::vector<std::vector<int>> dots) {

    int xmin = dots[0][0];
    int xmax = dots[0][0];
    int ymin = dots[0][1];
    int ymax = dots[0][1];

    for (const auto& dot : dots) 
    {
        xmin = std::min(xmin, dot[0]);
        xmax = std::max(xmax, dot[0]);
        ymin = std::min(ymin, dot[1]);
        ymax = std::max(ymax, dot[1]);
    }

    return (xmax-xmin)*(ymax-ymin);
}

int MinMaxSTL(const std::vector<std::vector<int>>& dots) {

    auto [minX, maxX] =
        std::minmax_element(dots.begin(), dots.end(),
                            [](auto &a, auto &b)
                            { return a[0] < b[0]; });

    auto [minY, maxY] =
        std::minmax_element(dots.begin(), dots.end(),
                            [](auto &a, auto &b)
                            { return a[1] < b[1]; });

    return ((*maxX)[0] - (*minX)[0]) * ((*maxY)[1] - (*minY)[1]);
}