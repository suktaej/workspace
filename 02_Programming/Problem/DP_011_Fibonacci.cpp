#include <vector>
#include <iostream>

int recFib(int n)
{
    if (n <= 1)
        return n;
    else
        return recFib(n - 1) + recFib(n - 2);
}

int dpFib(int n)
{
    int idx;
    std::vector<int> f(n);

    f[0] = 0;

    if (n > 0)
    {
        f[1] = 1;

        for(int i = 2; i<= n; ++i)
            f[i] = f[i-1] + f[i-2];
    }

    return f[n];
}

int main()
{
    std::cout<<recFib(10)<<'\n';
    std::cout<<dpFib(10)<<'\n';

    return 0;
}