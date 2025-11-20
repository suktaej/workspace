#include <vector>
#include <iostream>

using namespace std;

int FindMine(vector<vector<int>> board);

int main(int argc, char* argv[])
{
    vector<vector<int>> board, board2;
    board = {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 0, 0}};
    board2 = {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 1, 1, 0}, {0, 0, 0, 0, 0}};
    FindMine(board);
    
    return 0;
}

int FindMine(vector<vector<int>> board) 
{
    int adjacentMine = 0;

    for (int row = 0; row < board.size(); ++row)
    {
        for (int column = 0; column < board[row].size(); ++column)
        {
            if (board[row][column] == 1)
            {
                for (int i = row - 1; i <= row + 1; ++i)
                {
                    for (int j = column - 1; j <= column + 1; ++j)
                    {
                        if (i < 0 || j < 0 || i >= board.size() || j >= board[i].size())
                            continue;

                        if (board[i][j] == 0)
                        {
                            board[i][j] = 2;
                            ++adjacentMine;
                        }
                    }
                }
            }
        }
    }

    int answer = 0;

    for (int row = 0; row < board.size(); ++row)
        for (int col = 0; col < board[row].size(); ++col)
            if (board[row][col] == 0)
                ++answer;

    return answer;
}
