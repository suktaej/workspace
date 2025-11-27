#include <string>
#include <vector>
#include <numeric>

int GCD(int a, int b)
{
    return b ? GCD(b, a%b) : a;
}

int PrimeFactor(int a, int b) 
{
    int g = GCD(a,b);
    b /= g;

    int answer = 0;
    
    while(true)
    {
        if(1 == b)
        {
            answer = 1;
            break;
        }

        if(0 == b % 5)
            b /= 5;
        else if(0 == b % 2)
            b /= 2;
        else
        {
            answer = 2;
            break;
        }
    }

    return answer;
}

int Optimize(int a, int b)
{
    int g = GCD(a, b);
    b /= g;

    while (b % 2 == 0)
        b /= 2;
    while (b % 5 == 0)
        b /= 5;
    
    return (b==1) ? 1 : 2;
}