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