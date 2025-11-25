#include <iostream>
#include <string>

static constexpr int mazeSize = 5;
static constexpr int dirSize = 8;

bool HasWord(const char (*maze)[mazeSize], int x, int y, const std::string& word);

void BoggleWord()
{
    const char maze[mazeSize][mazeSize] = {
        {'U','R','L','P','M'},
        {'X','P','R','E','T'},
        {'G','I','A','E','T'},
        {'X','T','N','Z','Y'},
        {'X','O','Q','R','S'}};
    
    const std::string findWord = "PREETY";

    std::cout << (HasWord(maze, findWord, 1, 1) ? "true" : "false") << "\n";
}

bool HasWord(const char (*maze)[mazeSize], const std::string &word, int x, int y)
{
    constexpr int dx[dirSize] = {-1, 0, 1, -1, 1, -1, 0, 1};
    constexpr int dy[dirSize] = {-1, -1, -1, 0, 0, 1, 1, 1};
    
    // Base case1
    if( x >= mazeSize || x < 0 && 
        y >= mazeSize || y < 0)
        return false;
    
    // Base case2
    if(maze[x][y]!=word[0])
        return false;

    // Base case3
    if(1 == word.size())
        return true;
    
    for(int dir = 0; dir < dirSize; ++dir)
    {
        int nextX = x + dx[dir];
        int nextY = y + dy[dir];

        if (HasWord(maze, word.substr(1), nextX, nextY))
            return true;
    }
    return false;
}

int main(void)
{
    BoggleWord();
    return 0;
}
