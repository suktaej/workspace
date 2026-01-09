#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

#define ROW 9
#define COL 10

struct Pair 
{
    int x, y;
};

struct Node 
{
    int parentX, parentY; // 부모 노드의 좌표
    double g, h, f;       // f = g + h
};

// 유효한 좌표인지 확인
bool isValid(int row, int col) 
{
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

// 장애물인지 확인 (1이면 이동 가능, 0이면 장애물)
bool isUnBlocked(const std::vector<std::vector<int>>& grid, int row, int col) 
{
    return grid[row][col] == 1;
}

// 목적지에 도달했는지 확인
bool isDestination(int row, int col, Pair dest) 
{
    return row == dest.x && col == dest.y;
}

// 맨해튼 거리
double calculateHValue(int row, int col, Pair dest) 
{
    return (double)abs(row - dest.x) + abs(col - dest.y);
}

// 경로 출력 함수
void tracePath(const std::vector<std::vector<Node>>& nodeDetails, Pair dest) 
{
    std::cout << "Shortest Path: ";
    int row = dest.x;
    int col = dest.y;
    std::vector<Pair> path;

    while (!(nodeDetails[row][col].parentX == row &&
             nodeDetails[row][col].parentY == col))
    {
        path.push_back({row, col});
        int temp_row = nodeDetails[row][col].parentX;
        int temp_col = nodeDetails[row][col].parentY;
        row = temp_row;
        col = temp_col;
    }

    path.push_back({row, col});
    reverse(path.begin(), path.end());

    for (auto p : path) 
        std::cout << "(" << p.x << "," << p.y << ") -> ";
    
    std::cout << "Done" << std::endl;
}

void aStarSearch(const std::vector<std::vector<int>>& grid, Pair src, Pair dest) 
{
    if (!isValid(src.x, src.y) || !isValid(dest.x, dest.y)) return;
    if (!isUnBlocked(grid, src.x, src.y) || !isUnBlocked(grid, dest.x, dest.y)) return;
    if (isDestination(src.x, src.y, dest)) return;

    // 방문 여부 확인
    bool closedList[ROW][COL];

    for(int i=0; i<ROW; i++) 
        for(int j=0; j<COL; j++) 
            closedList[i][j] = false;

    // 각 노드에 대한 상세 정보 (f, g, h, parent)
    std::vector<std::vector<Node>> nodeDetails(ROW, std::vector<Node>(COL, {-1, -1, INFINITY, INFINITY, INFINITY}));

    // 시작 노드 설정
    int i = src.x, j = src.y;
    nodeDetails[i][j].f = 0.0;
    nodeDetails[i][j].g = 0.0;
    nodeDetails[i][j].h = 0.0;
    nodeDetails[i][j].parentX = i;
    nodeDetails[i][j].parentY = j;

    // 우선순위 큐 정의 (f값이 작은 순서대로 정렬)
    // <f값, <x좌표, y좌표>>
    typedef std::pair<double, std::pair<int, int>> pPair;
    std::priority_queue<pPair, std::vector<pPair>, std::greater<pPair>> openList;

    openList.push({0.0, {i, j}});

    bool foundDest = false;

    // 상, 하, 좌, 우 이동 방향
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!openList.empty()) 
    {
        pPair p = openList.top();
        openList.pop();

        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        // 4가지 방향 탐색
        for (int dir = 0; dir < 4; dir++) 
        {
            int ni = i + dx[dir];
            int nj = j + dy[dir];

            if (isValid(ni, nj)) 
            {
                if (isDestination(ni, nj, dest)) 
                {
                    nodeDetails[ni][nj].parentX = i;
                    nodeDetails[ni][nj].parentY = j;
                    tracePath(nodeDetails, dest);
                    foundDest = true;
                    return;
                }
                else if (!closedList[ni][nj] && isUnBlocked(grid, ni, nj)) 
                {
                    double gNew = nodeDetails[i][j].g + 1.0;
                    double hNew = calculateHValue(ni, nj, dest);
                    double fNew = gNew + hNew;

                    if (nodeDetails[ni][nj].f == INFINITY || nodeDetails[ni][nj].f > fNew) 
                    {
                        openList.push({fNew, {ni, nj}});
                        nodeDetails[ni][nj].f = fNew;
                        nodeDetails[ni][nj].g = gNew;
                        nodeDetails[ni][nj].h = hNew;
                        nodeDetails[ni][nj].parentX = i;
                        nodeDetails[ni][nj].parentY = j;
                    }
                }
            }
        }
    }

    if (!foundDest) std::cout << "Not found" << std::endl;
}

int main() {
    // 1은 이동 가능, 0은 장애물
    std::vector<std::vector<int>> grid = {
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 1, 0, 1, 1},
        {1, 1, 1, 0, 1, 1, 0, 1, 0, 1},
        {0, 0, 1, 0, 1, 0, 0, 0, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
        {1, 0, 1, 1, 1, 1, 0, 1, 0, 0},
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 1, 0, 0, 1}
    };

    Pair src = {8, 0};  // 시작점
    Pair dest = {0, 0}; // 도착점

    aStarSearch(grid, src, dest);

    return 0;
}