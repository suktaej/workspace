#include <vector>
#include <array>
#include <iostream>

template <size_t N>
using squMat = std::array<std::array<long long, N>, N>;

int rec(int n)
{
    if (1 >= n)
        return n;
    else
        return rec(n-1) + rec(n-2);
}

int dp(int n)
{
    std::vector<int> dp(n,0);

    dp[0] = 1;
    dp[1] = 1;

    for (int i = 2; i < n; ++i)
        dp[i] = dp[i - 1] + dp[i - 2];

    return dp[n-1];
}

template <size_t N>
squMat<N> matMul(const squMat<N>& A,const squMat<N>& B)
{
    squMat<N> C = {{}};

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int k = 0; k < N; ++k)
                C[i][j] += A[i][k] * B[k][j];

    return C;
}

long long power(int n)
{
    if (n <= 1)
        return n;

    // 초기 결과 행렬은 단위행렬
    squMat<2> res = {{{1,0},{0,1}}};
    squMat<2> base = {{{1,1},{1,0}}};

    // 알고있는 항은 a_1 = 1만을 가정
    int exp = n - 1;

    while(exp > 0)
    {
        if(exp%2 == 1)
            res = matMul(res,base);
        
        base = matMul(base, base);
        exp /= 2;
    }

    return res[0][0];
}

long long power(int n, int coef1, int coef2, int coef3)
{
    // 초기 항 예외처리
    if(n == 1) return 1;
    if(n == 2) return 1;
    if(n == 3) return 2;

    // 초기 값 설정
    long long a1 = 1;
    long long a2 = 1;
    long long a3 = 2;

    squMat<3> res = {{{1,0,0},{0,1,0},{0,0,1}}};
    squMat<3> base = {{{coef1, coef2, coef3}, {1, 0, 0}, {0, 1, 0}}};
    
     // M^(n-3) 계산 (n=4일 때 1번 곱해야 하므로 n-3)
     // 내가 가진 초기 정보값 만큼을 제외
    int exp = n - 3;

    while(exp > 0)
    {
        if(exp%2 == 1)
            res = matMul(res,base);
        
        base = matMul(base, base);
        exp /= 2;
    }

    // M^(n-3) * [a3, a2, a1] 벡터의 첫 번째 행 계산
    // a_n = res[0][0]*a3 + res[0][1]*a2 + res[0][2]*a1
    long long ans = (res[0][0] * a3);
    ans = (ans + res[0][1] * a2);
    ans = (ans + res[0][2] * a1);

    return ans;
}

int main()
{
    int n = 10;

    std::cout<<rec(n)<<'\n';
    std::cout<<dp(n)<<'\n';
    std::cout<<power(n);

    return 0;
}