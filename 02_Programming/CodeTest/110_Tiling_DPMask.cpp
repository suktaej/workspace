#include <iostream>
#include <vector>

int m, n;

struct Mat
{
    int size;
    std::vector<std::vector<int>> mat;

    Mat(int s) : size(s)
    {
        mat.assign(size, std::vector<int>(size,0));
    }

    Mat operator*(const Mat& other) const
    {
        Mat res(size);

        for(int i =0;i<size;++i)
        {
            for(int j= 0; j<size;++j)
            {
                if(mat[i][j] == 0)
                    continue;

                for (int k = 0; k < size; ++k)
                    res.mat[i][k] += mat[i][j] * other.mat[j][k]; 
            }
        }

        return res;
    }

    void Set(int s)
    {
        size = s;
        mat.assign(size, std::vector<int>(size,0));
    }
};

Mat T(0);

Mat power(Mat mat, int exp)
{
    Mat res(mat.size);

    for (int i = 0; i < mat.size; ++i)
        res.mat[i][i] = 1;

    while(exp > 0)
    {
        if (exp % 2 == 1)
            res = res * mat;

        mat = mat * mat;
        exp /= 2;
    }

    return res;
}

void dfs(int curRow, int curMask, int nextMask)
{
    if(curRow == m)
    {
        T.mat[nextMask][curMask]++;
        return;
    }

    if(curMask & (1<<curRow))
        dfs(curRow + 1, curMask, nextMask);
    else
    {
        dfs(curRow+1, curMask, nextMask | (1<<curRow));

        if(curRow+1 < m && !(curMask & (1<<(curRow+1))))
            dfs(curRow+2,curMask,nextMask);
    }
}

int solve()
{
    if ((m * n) % 2 != 0)
        return;
    
    int states = (1 << m);
    T.Set(states);

    for(int i=0; i<states;++i)
        dfs(0,i,0);
}

int main()
{
    std::cin>>m>>n;
    solve();

    return 0;
}