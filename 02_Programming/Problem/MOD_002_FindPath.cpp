#include <iostream>
#include <vector>
#include <array>

constexpr int MOD = 1000000007;

int dpfindPaths(int row, int col)
{
    std::vector<std::vector<int>> dp(row + 1, std::vector<int>(col + 1, 0));

    dp[0][0] = 1;

    for (int y = 0; y <= row; ++y)
    {
        for (int x = 0; x <= col; ++x)
        {
            if( 0 == y && 0 == x)
                continue;

            int left = (x > 0) ? dp[y][x-1] : 0;
            int down = (y > 0) ? dp[y-1][x] : 0;
            
            dp[y][x] = left + down;
        }
    }

    return dp[row][col];
}

int dpMod(int row, int col)
{
    std::vector<std::vector<long long>> dp(row + 1, std::vector<long long>(col + 1, 0));
    long long mod = 1e9 + 7;

    dp[0][0] = 1;

    for (int y = 0; y <= row; ++y)
    {
        for (int x = 0; x <= col; ++x)
        {
            if( 0 == y && 0 == x)
                continue;

            long long left = (x > 0) ? dp[y][x-1] : 0;
            long long down = (y > 0) ? dp[y-1][x] : 0;

            dp[y][x] = (left + down) % mod;
        }
    }

    return dp[row][col];
}

int combine(int n, int r)
{
    long long res = 1;

    for (int i = 0; i < r; ++i)
    {
        int temp = (n - i) / (i + 1);
        res *= temp;
    }

    return static_cast<int>(res);
}

long long power(long long base, long long exp)
{
    long long res = 1;
    base %= MOD;

    // 반복제곱
    while(exp > 0)
    {
        // 지수가 홀수라면 현재 base를 결과에 한 번 곱
        if (exp % 2 == 1)
            res = (res * base) % MOD;
        // 지수를 반으로 줄이고 base는 제곱
        base = (base * base) % MOD;
        exp /= 2;
    }

    return res;
}

// 페르마의 소정리 : b의 모듈러 역수를 구하는 함수(b^(mod-2))
long long modInverse(long long n)
{
    return power(n, MOD - 2);
}

int combineMod(int n, int r) 
{
    if (r < 0 || r > n) 
        return 0;

    if (r == 0 || r == n)
        return 1;

    if (r > n / 2)
        r = n - r; // nCr = nC(n-r) 성질 활용

    long long res = 1;

    // case 1 : 매 연산 시 분자/분모를 계산 후 반환
    /*
    for (int i = 0; i < r; ++i)
    {
        // 분자 곱하기: res = (res * (n - i)) % mod
        res = (res * (n - i)) % MOD;

        // 분모 나누기 대신 역수 곱하기: res = (res * (i + 1)^-1) % mod
        res = (res * modInverse(i + 1)) % MOD;
    }
    
    return static_cast<int>(res);
    */

    // case 2 : 마지막에 분모의 역수를 1회만 연산
    long long num = 1; // 분자 (Numerator)
    long long den = 1; // 분모 (Denominator)

    for (int i = 0; i < r; ++i) 
    {
        num = (num * (n - i)) % MOD;
        den = (den * (i + 1)) % MOD;
    }

    // 마지막에 분모의 역수를 딱 한 번만 곱함
    return (num * modInverse(den)) % MOD;   
}

bool isPrime(long long n) 
{
    if (n <= 1) 
        return false;
    if (n <= 3) 
        return true;
    if (n % 2 == 0 || n % 3 == 0) 
        return false;

    // 2와 3을 제외하고, 제곱근까지만 확인
    for (long long i = 5; i * i <= n; i += 6) 
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    
    return true;
}

int main()
{
    if(isPrime(static_cast<int>(std::sqrt(MOD))))
        std::cout << combineMod(860, 120);

    return 0;
}