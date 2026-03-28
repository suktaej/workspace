#include <vector>
#include <array>
#include <iostream>

const std::array<int, 6> idx = {0, 1, 2, 3, 4, 5};

int DFS(int pos)
{
    int size = static_cast<int>(idx.size());

    if (size - 1 == pos)
        return 1;
    if (size <= pos)
        return 0;

    int count = 0;

    count += DFS(pos + 1);
    count += DFS(pos + 2);

    return count;
}

int main()
{
    std::cout<<DFS(0);
    return 0;
}