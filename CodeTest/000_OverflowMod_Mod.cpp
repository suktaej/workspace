#include <iostream>
#include <vector>

long long gcd(long long a, long long b)
{
    return b ? a : gcd(b, a % b);
}

long long dpFibMod(long long n, long long mod)
{
    long long prev1 = 1;
    long long prev2 = 1;
    long long res = 0;

    for (long long i = 2; i < n; ++i)
    {
        res = (prev1 + prev2) % mod;
        prev2 = prev1;
        prev1 = res;
    }

    return res;
}

void fibMod()
{
    long long term = 8691200;
    long long mod = 1000000007;

    long long value = dpFibMod(term, mod);

    std::cout << (value % mod);
}

void expMod()
{
    int exp = 23;
    int base = 5;
    int mod = 1000000007;
    long long res = 1;

    for (int i = 1; i <= exp; ++i)
        res = (res * base) % mod;

    std::cout<<res;
}

int main()
{
    expMod();
    return 0;
}