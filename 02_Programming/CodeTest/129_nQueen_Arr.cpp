#include <iostream>

constexpr int maxSize = 15;
int size;
int res = 0;
bool colUsed[maxSize+1];
bool lDiagUsed[maxSize*2+1]; // row + col
bool rDiagUsed[maxSize*2+1]; // row - col + N

void solve(int row)
{
    if(row > size)
    {
        ++res;
        return;
    }

    for (int col = 1; col <= size; ++col)
    {
        if (!colUsed[col] &&
            !lDiagUsed[row + col] &&
            !rDiagUsed[row - col + size])
        {
            colUsed[col] = lDiagUsed[row+col] = rDiagUsed[row-col+size] = true;
            solve(row+1);
            colUsed[col] = lDiagUsed[row+col] = rDiagUsed[row-col+size] = false;
        }
    }
}

unsigned int column = 0;
unsigned int lDiag = 0;
unsigned int rDiag = 0;

void bitSolve(int row)
{
    if(row > size)
    {
        ++res;
        return;
    }

    for (int col = 1; col <= size; ++col)
    {
        if (!(column & (1 << col)) &&
            !(lDiag & (1 << (row + col))) &&
            !(rDiag & (1 << (row - col + size))))
        {
            column |= (1 << col);
            lDiag |= (1 << (row + col));
            rDiag |= (1 << (row - col + size));
            
            solve(row+1);
            
            column &= ~(1 << col);
            lDiag &= ~(1 << (row + col));
            rDiag &= ~(1 << (row - col + size));
        }
    }
}

int main()
{
    std::cin>>size;
    solve(1);
    std::cout<<res;

    return 0;
}