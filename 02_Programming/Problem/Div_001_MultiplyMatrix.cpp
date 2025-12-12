#include <vector>

class SquareMatrix
{
public:
    SquareMatrix(std::vector<std::vector<int>> vec)
    : mat(vec){}

private:
    std::vector<std::vector<int>> mat;

public:
    SquareMatrix Identity(int n);
    SquareMatrix Pow(const SquareMatrix& m, int exp);

public:
    int size() const { return mat.size(); }
    
    SquareMatrix operator*(const int& val)
    {
        int n = size();
        std::vector<std::vector<int>> res(n, std::vector<int>(n, 0));
        
        for(int i=0;i<n;++i)
            for (int j = 0; j < n; ++j)
                res[i][j] += mat[i][j] * val;
        
        return SquareMatrix(res);
    }

    SquareMatrix operator*(const SquareMatrix& other)
    {
        int n = size();
        std::vector<std::vector<int>> res(n, std::vector<int>(n, 0));

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    res[i][j] += mat[i][k] * other.mat[k][j];

        return SquareMatrix(res);
    }
};

int FastSum(int n)
{
    if (n == 1)
        return 1;

    if (n % 2 == 1)
        return FastSum(n - 1) + n;

    return 2 * FastSum(n / 2) + (n / 2) * (n / 2);
}

int RecSum(int n)
{
    if(n == 1)
        return 1;
    
    return n + RecSum(n-1);
}

inline SquareMatrix SquareMatrix::Identity(int n)
{
    std::vector<std::vector<int>> id(n, std::vector<int>(n, 0));
    
    for (int i=0; i<n; i++)
        id[i][i] = 1;

    return SquareMatrix(id);
}

inline SquareMatrix SquareMatrix::Pow(const SquareMatrix &m, int exp)
{
    if (exp == 0)
        return Identity(m.size());

    if (exp % 2 == 1)
        return Pow(m, exp - 1) * m;

    SquareMatrix half = Pow(m, exp / 2);
    return half * half;
}