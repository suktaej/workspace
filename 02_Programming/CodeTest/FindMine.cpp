#include <vector>
#include <iostream>

using namespace std;

int FindMine(vector<vector<int>> board) 
{
    int answer = 0;
    
    for(int row = 0; row < board.size(); ++row)
    {
        for(int column = 0; column < board[row].size(); ++column)
        {
            cout<<"i:"<<row<<"j:"<<column<<"mine:"<<board[row][column]<<endl;
            
            if(board[row][column] == 1)
            {
                for(int i = row -1 ; i <= row +1 ; ++i)
                {
                    for(int j = column -1 ; j <= column+1; ++j)
                    {
                        if(board[i][j] == 0)
                        {
                            board[i][j] = 2;
                            ++answer;
                        }
                    }
                }        
            }
        }
    }
    
    return answer;
}
