#include <iostream>

int fibo(int a)
{
    if (a == 1)
        return 1;
    if (a <= 0)
        return 0;

    int num = fibo(a-1) + fibo(a-2);

    return num;
}

int tailfibo(int n, int a = 0, int b = 1)
{
    if(n==0)
        return a;
    if(n==1)
        return b;

    return tailfibo(n-1,b, a+b);
}

constexpr int arrSize = 64;
int dp[arrSize] = {0,};

void dpfibo()
{
    dp[0] = 0;
    dp[1] = 1;

    for(int i=2;i<arrSize;++i)
        dp[i] = dp[i-1]+dp[i-2];
}

int whilefibo(int n)
{
    if (n <= 1) 
        return n;

    int prev = 0;
    int cur = 1;
    int idx = 2;

    while(idx <= n)
    {
        int next = prev + cur;
        prev = cur;
        cur = next;
        ++idx;
    }

    return cur;
}

int main()
{
    // 1 1 2 3 5 8 13
    int k = 5;
    dpfibo();
    std::cout<<dp[k]<<' '<<fibo(k)<<' '<<whilefibo(k)<<' '<<tailfibo(k);

    return 0;
}