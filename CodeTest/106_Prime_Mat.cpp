#include <iostream>
#include <cmath>
#include <vector>

void CountPrimes(int low, int high, std::vector<int>& res)
{
    if (high < 2 || low > high)
        return;

    std::vector<bool> isPrime(high + 1, true);
    isPrime[0]=false;
    isPrime[1]=false;

    for (int i = 2; i * i <= high; ++i)
        if(isPrime[i])
            for (int j = i * i; j <= high; j += i)
                isPrime[j] = false;

    res.clear();

    for (int i = low; i <= high; ++i)
        if(isPrime[i])
            res.push_back(i);

    for(int n : res)
        std::cout<<n<<'\n';
}

int main()
{
    int low, high;
    std::vector<int> res;

    std::cin>>low>>high;
    CountPrimes(low, high, res);

    return 0;
}