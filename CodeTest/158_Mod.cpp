#include <iostream>

long long pow(long long base, long long exp, long long mod)
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

    return res % mod;
}

long long recursive_pow(long long a, long long b, long long c) {

    if (b == 0) 
        return 1;
    
    if (b == 1) 
        return a % c;
    
    long long half = recursive_pow(a, b / 2, c);
    half = (half * half) % c; // a^(b/2) * a^(b/2)
    
    if (b % 2 == 0) 
        return half;
     else 
        return (half * (a % c)) % c; // 홀수일 경우 a를 한 번 더 곱함
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long n, m, l;
    std::cin >> n >> m >> l;
    std::cout<<pow(n,m,l);
}