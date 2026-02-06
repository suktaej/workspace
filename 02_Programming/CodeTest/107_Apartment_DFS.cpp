#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

std::string gMap[25];
int n;
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int dfs(int y, int x)
{
    if (y < 0 || x < 0 || y >= n || x >= n)
        return 0;

    if (gMap[y][x] == '0')
        return 0;

    gMap[y][x] = '0';
    int cnt = 1;

    for(int i=0;i<4;++i)
        cnt += dfs(y+dy[i], x+dx[i]);

    return cnt;
}

int main()
{
    std::cin >> n;

    for (int i = 0; i < n; ++i)
        std::cin >> gMap[i];

    std::vector<int> estate;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (gMap[i][j] == '1')
                estate.push_back(dfs(i,j));

    std::sort(estate.begin(), estate.end());

    std::cout << estate.size() << "\n";
    for (int i : estate)
        std::cout << i << '\n';

    return 0;
}