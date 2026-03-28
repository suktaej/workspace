#include <iostream>
#include <vector>

enum class ESHAPE : uint8_t
{
    HOR,
    VER,
    REHOR,
    REVER,
    SIZE
};

constexpr int blockSize = 3;

const int coverType[static_cast<int>(ESHAPE::SIZE)][blockSize][2] = {
    {{0, 0}, {1, 0}, {0, 1}},
    {{0, 0}, {0, 1}, {1, 1}},
    {{0, 0}, {1, 0}, {1, 1}},
    {{0, 0}, {1, 0}, {1, -1}}};

bool SetBlock(std::vector<std::vector<int>>& board, int y, int x, ESHAPE type, int delta)
{
    bool bPlaced = true;

    for(int i = 0; i < blockSize; ++i)
    {   
        // 탐색범위 지정
        const int ny = y + coverType[static_cast<int>(type)][i][0];
        const int nx = x + coverType[static_cast<int>(type)][i][1];

        // out of bound 확인
        if(ny < 0 || nx < 0 || ny >= board.size() || nx >= board[0].size())
            bPlaced = false;
        else if ((board[ny][nx] += delta) > 1)
            bPlaced = false;
    }

    return bPlaced;
}

int Cover(std::vector<std::vector<int>>& board)
{
    // 채우지 못한 칸들 중 최상단 좌측에 위치한 칸을 탐색
    int x = -1;
    int y = -1;

    for(int i = 0; i < board.size(); ++i)
    {
        for(int j =0; j < board[i].size();++j)
        {
            if(board[i][j] == 0)
            {
                y = i;
                x = j;
                break;
            }
        }

        if (y != -1)
            break;
    }
    // Base case : 모든 칸을 채웠으면 1을 반환
    if(y == -1)
        return 1;
 
    // board에 block을 삽입
    int result = 0;

    for (int i = 0; i < static_cast<int>(ESHAPE::SIZE); ++i)
    {
        ESHAPE type = static_cast<ESHAPE>(i);
     
        // Recursion
        if(SetBlock(board,y,x,type,1))
            result += Cover(board);

        // 블록 제거
        SetBlock(board,y,x,type,-1);
    }

    return result;
}

int main(void)
{
    std::vector<std::vector<int>> board = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}};

    int ways = Cover(board);
    std::cout << "Ways: " << ways << std::endl;
}