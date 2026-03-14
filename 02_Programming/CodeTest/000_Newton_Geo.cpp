#include <iostream>

void Newton()
{
    double radicand = 2.0;
    int iterations = 5;

    double x = 1.0;

    for (int i = 0; i < iterations; ++i)
    {
        double fx  = x * x - radicand;   // f(x)
        double dfx = 2.0 * x;            // f'(x)

        double nextX = x - fx / dfx;
        x = nextX;

        std::cout << x << std::endl;
    }
}

void Newton()
{
    double radicand = 2.0;
    int iterations = 5;

    double x = radicand;  // 초기 추정값

    for (int i = 0; i < iterations; ++i)
    {
        x = 0.5 * (x + radicand / x);
        std::cout << x << std::endl;
    }
}