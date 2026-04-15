#include <iostream>

int power(int base, int exp)
{
    int res = 1;
    
    while (exp > 0)
    {
        if(exp & 1)
            res *= base;

        base *= base;
        exp = exp >> 1 ;
    }

    return res;
}