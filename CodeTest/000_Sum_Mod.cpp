#include <iostream>
#include <vector>

long long dncExp(long long base, long long exp, long long mod)
{
    long long res = 1;
    base %= mod;

    while (exp > 0)
    {
        if (exp % 2 == 1)
            res = (res * base) % mod;

        base = (base * base) % mod;
        exp /= 2;
    }

    return res;
}

/* 
    등비수열의 합(0 ~ n-1)
    S  = a + ax + ax^2 ... ax^n-1
    xS = ax + ax^2 ... ax&n-1 + ax^n
    S(1-x) = a - ax^n = a(1-x^n)
*/

long long sigma(int n)
{
    constexpr long long mod = 1e9 + 7;
    constexpr long long base = 4;
    
    // long long res = 0;
    // for (int i = 0; i <= n; ++i)
    //     res = (res + dncExp(base, i, mod)) % mod;

    //  a(r^(n+1) - 1) / (r-1)
    long long numerator = (dncExp(base, n + 1, mod) - 1 + mod) % mod;
    
    // a/b=c(mod d) == a*x=c(mod d)
    // x = b^(mod-2)
    // 페르마 소정리
    long long inv3 = dncExp(base - 1, mod - 2, mod);

    return (numerator * inv3) % mod;
}


int main()
{
    int n = 45;
    std::cout<<sigma(n);
    return 0;
}