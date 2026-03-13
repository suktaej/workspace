#include <iostream>
#include <vector>
// #include <bits/stdc++.h>

constexpr int height = 3;
int width;

struct Mat
{
    int size;
    std::vector<std::vector<long long>> dp;

    Mat(int i) : size(i)
    {
        dp.assign(size, std::vector<long long>(size,0));
    }

    Mat operator*(const Mat& other) const
    {
        Mat res(size);

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
            {
                if(dp[i][j] == 0)
                    continue;

                for (int k = 0; k < size; ++k)
                    res.dp[i][k] += (dp[i][j] * other.dp[j][k]);
            }

        return res;
    }

    void Set(int s)
    {
        size = s;
        dp.assign(size, std::vector<long long>(size,0));
    }
};

Mat M(0);

Mat power(Mat m, int exp)
{
    Mat res(m.size);

    // make I
    for(int i =0; i< m.size; ++i)
        res.dp[i][i] = 1;

    while (exp > 0)
    {
        if (exp % 2 == 1)
            res = res * m;

        m = m * m;
        exp /= 2;
    }

    return res;
}

void fillMat(int row, int curMask, int nextMask)
{
    if(row == height)
    {
        ++M.dp[curMask][nextMask];
        return;
    }

    if(curMask & (1 << row))
        fillMat(row+1,curMask, nextMask);
    else
    {
        fillMat(row+1, curMask, nextMask | (1<<row));

        if (row + 1 < height &&
            0 == (curMask & (1 << (row + 1))))
            fillMat(row+2, curMask, nextMask);
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cin>>width;

    if (width * height % 2 == 1)
    {
        std::cout<<"No";
        return 0;
    }

    int state = 1 << height;

    M.Set(state);

    for(int i=0;i<state;++i)
        fillMat(0,i,0);

    Mat res = power(M, width);
    std::cout<<res.dp[0][0];
    
    return 0;
}