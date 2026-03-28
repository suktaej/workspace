#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

struct Box
{
    int x;
    int y;
    int z;
};

int w,d,h;
int unripe = 0;
std::vector<Box> ripes;
// std::vector<std::vector<std::vector<int>>> grid;
int grid[101][101][101] = {0,};

void bfs()
{
    int dx[] = {1, -1, 0, 0, 0, 0};
    int dy[] = {0, 0, 1, -1, 0, 0};
    int dz[] = {0, 0, 0, 0, 1, -1};
    int days = 0;
    
    std::queue<Box> q;
    
    for(auto it : ripes)
        q.push(it);

    while(!q.empty())
    {
        int lev = q.size();
        bool progressed = false;

        while(lev--)
        {
            auto [cx, cy, cz] = q.front();
            q.pop();

            for(int i=0;i<6;++i)
            {
                int nx = cx+dx[i];
                int ny = cy+dy[i];
                int nz = cz+dz[i];

                if (nx < 0 || ny < 0 || nz < 0 || nx >= w || ny >= d || nz >= h)
                    continue;

                if(grid[nz][ny][nx] == 0)
                {
                    q.push({nx, ny, nz});
                    grid[nz][ny][nx] = 1;
                    --unripe;
                    progressed = true;
                }
            }
        }

        if(progressed) ++days;
    }

    if (unripe == 0)
        std::cout << days;
    else
        std::cout<< -1;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cin>>w>>d>>h;
    // grid.assign(h,std::vector<std::vector<int>>(d,std::vector<int>(w,0)));

    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < d; ++j)
        {
            for (int k = 0; k < w; ++k)
            {
                int temp;
                std::cin>>temp;

                if (temp != 0) grid[i][j][k] = temp;
                if (temp == 0) ++unripe;
                if (temp == 1) ripes.push_back({k, j, i});
            }
        }
    }

    if (unripe == 0)
        std::cout<<0;
    else
        bfs();

    return 0;
}