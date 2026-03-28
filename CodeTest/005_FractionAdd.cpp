#include <iostream>
#include <vector>
#include <numeric>

int gcd(int a, int b)
{
    if (0 == b)
        return a;

    return gcd(b, a%b);
}

int lcm(int a, int b)
{
    return (a*b)/gcd(a,b);
}

int ternaryGCD(int a, int b)
{
    return b ? a : gcd(b, a%b);
}

int loopGCD(int a, int b)
{
    while (b != 0)
    {
        int temp = a % b;
        a = b;
        b = temp;
    }

    return a;
}

int main(void)
{
    return 0;
}

std::vector<int> FractionAdd(int numer1, int denom1, int numer2, int denom2) {
   
    std::vector<int> answer;

    int lcm = std::lcm(denom1, denom2);
    numer1 *= lcm / denom1;
    numer2 *= lcm / denom2;
    numer1 += numer2;

    int gcd = std::gcd(numer1, lcm);

    numer1 /= gcd;
    lcm /= gcd;

    answer.push_back(numer1);
    answer.push_back(lcm);

    return answer;
}