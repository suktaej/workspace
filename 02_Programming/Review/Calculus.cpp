#include <vector>
#include <functional>
#include <cmath>
#include <iostream>

float DegToRad(float deg)
{
    constexpr float PI = 3.141592f;
    constexpr float RAD = 180.f;

    return deg * (PI/RAD);
}

template <typename T>
double Derivative(T&& func, double x)
{
    constexpr double h = 1e-6;
    return (func(x + h) - func(x - h)) / (2.0 * h);
}

template <typename F>
double IntegrateTrapezoid(F&& func, double a, double b, int n)
{
    double h = (b - a) / n;
    // 한 구간은 h/2(f(x)+f(x+1))
    // 전 구간을 합할 경우
    // h/2{f(x0)+2f(x1)+2f(x2)...+2f(xn-1)+f(xn)}
    // 첫 구간과 마지막 구간의 1회 합이 추가로 필요
    double sum = 0.5 * (func(a) + func(b));

    for (int i = 1; i < n; ++i)
        sum += func(a + i * h);

    return sum * h;
}

template <typename F>
double IntegrateMidpoint(F&& f,double a, double b, int n)
{
    double h = (b - a) / n;
    double sum = 0.0;

    for (int i = 0; i < n; ++i)
    {
        double x = a + (i + 0.5) * h;
        sum += f(x);
    }

    return sum * h;
}

int main()
{
    auto f1 = [](double x) { return x * x + std::sin(x); };
    double d = Derivative(f1, 1.f);
    // std::cout<<d;

    auto f2 = [](double x) { return pow(2, x * x); };
    double I = IntegrateTrapezoid(f2, 0, 1, 1000);
    std::cout<<I;
    return 0;
}