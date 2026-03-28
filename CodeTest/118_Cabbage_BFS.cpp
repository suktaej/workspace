#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

int testCount;
int row, col, k;
// std::vector<std::vector<bool>> map;
bool map[51][51];

int dx[] ={1,-1,0,0};
int dy[] ={0,0,1,-1};

void BFS(int i, int j)
{
    std::queue<std::pair<int, int>> q;

    q.push({i, j});
    map[i][j] = 0;

    while (!q.empty())
    {
        auto [y, x] = q.front();
        q.pop();

        for (int dir = 0; dir < 4; ++dir)
        {
            int nx = dx[dir] + x;
            int ny = dy[dir] + y;

            if (nx < 0 || nx >= col || ny < 0 || ny >= row)
                continue;

            if (map[ny][nx] == true)
            {
                q.push({ny, nx});
                map[ny][nx] = false;
            }
        }
    }
}

void solve()
{   
    int res = 0;
    
    for(int i=0;i<row;++i)
        for(int j=0;j<col;++j)
        {
            if (map[i][j] == 1)
            {
                BFS(i,j);
                ++res;
            }
        }

    std::cout<<res<<'\n';
    // map.clear();
}

int main(void)
{
    std::cin>>testCount;

    for(int i =0;i<testCount;++i)
    {
        std::cin >> col >> row >> k;
        memset(map,false,sizeof(map));
        // map.resize(row, std::vector<bool>(col, false));

        for(int j=0;j<k;++j)
        {
            int x, y;
            std::cin >> x >> y;
            map[y][x] = true;
        }

        solve();
    }
    
    return 0;
}