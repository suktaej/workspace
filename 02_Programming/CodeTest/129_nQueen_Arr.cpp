#include <iostream>
#include <vector>

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

int main()
{
    std::cin>>size;
    solve(1);
    std::cout<<res;

    return 0;
}