#include <vector>
#include <limits>
#include <iostream>

static constexpr int city = 10;
const int dist[city][city] = {
    {0, 29, 20, 21, 16, 31, 100, 12, 4, 31},
    {29, 0, 15, 29, 28, 40, 72, 21, 29, 41},
    {20, 15, 0, 15, 14, 25, 81, 9, 23, 27},
    {21, 29, 15, 0, 4, 12, 92, 12, 25, 13},
    {16, 28, 14, 4, 0, 16, 94, 9, 20, 16},
    {31, 40, 25, 12, 16, 0, 95, 24, 36, 3},
    {100, 72, 81, 92, 94, 95, 0, 90, 101, 99},
    {12, 21, 9, 12, 9, 24, 90, 0, 15, 25},
    {4, 29, 23, 25, 20, 36, 101, 15, 0, 35},
    {31, 41, 27, 13, 16, 3, 99, 25, 35, 0}
};

int ShortestPath(std::vector<int> &path, std::vector<bool> &visited, int current)
{
    if (path.size() == city)
        return current + dist[path.back()][path[0]];

    int result = std::numeric_limits<int>::max();
    int here = path.back();

    for (int next = 0; next < city; ++next)
    {
        if (visited[next]) continue;

        visited[next] = true;
        path.push_back(next);

        int cand = ShortestPath(path, visited, current + dist[here][next]);
        result = std::min(result, cand);

        path.pop_back();
        visited[next] = false;
    }
    return result;
}

int main()
{
    std::vector<int> path = {0};
    std::vector<bool> visited(city, false);

    visited[0] = true;

    std::cout << ShortestPath(path, visited, 0);
}
