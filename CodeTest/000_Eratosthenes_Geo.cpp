#include <vector>
#include <cmath>
#include <iostream>

int AliquotCount(int n)
{
    int count = 0;
    // std::vector<int> vec;
    int sq = std::sqrt(n);

    for (int i = 2; i <= sq; ++i)
    {
        if (n % i == 0)
        {
            // vec.push_back(i);
            ++count;
        
            if (i != n/i)
            {
                // vec.push_back(n/i);
                ++count;
            }
        }
    }

    return count;
}

int IsPrime(int n)
{
    int sq = std::sqrt(n);

    for (int i = 2; i <= sq; ++i)
        if (n % i == 0)
            return false;

    return true;
}

int CountPrimes(int n)
{
    if (n < 2)
        return 0;

    std::vector<bool> primes(n + 1, true);
    primes[0] = false;
    primes[1] = false;

    int limit = std::sqrt(n);

    for(int i =2; i<= limit; ++i)
        if(primes[i])
            for (int j = i * i; j <= n; j += i)
                primes[j] = false;

    int count = 0;
    for (int i = 2; i <= n; ++i)
        if(primes[i])
            ++count;

    return count;
}

long SumOfDivisorsCount(int n)
{
    std::vector<int> divCount(n + 1, 0);

    for (int i = 1; i <= n; ++i)
        for (int j = i; j <= n; j += i)
            ++divCount[j];

    long sum = 0;
    
    for (int i = 1; i <= n; ++i)
        sum += divCount[i];

    return sum;
}

int main()
{
    std::cout << SumOfDivisorsCount(4);
    return 0;
}