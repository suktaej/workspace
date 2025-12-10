#include <iostream>

int Recursion_fib(int n)
{
    if(n <= 1)
        return n;

    return Recursion_fib(n-1) + Recursion_fib(n-2);
}

int TailRecursion_fib(int n, int a = 0, int b = 1)
{
    if(n == 0)
        return a;
    if(n == 1)
        return b;

    return TailRecursion_fib(n-1, b, a+b);
}

void Hanoi(int n, char from, char to, char temp)
{
    static int count = 0;

    if(n == 0)
        return;

    Hanoi(n-1, from, temp, to); // n-1개의 원판을 from->temp

    std::cout<<"Move disk "<<n<<" from "<<from<<" to "<<to<<std::endl; // from에서 가장 바닥의 원판을 to로 이동
    ++count;

    Hanoi(n-1, temp, to, from); //n-1개의 원판을 temp->to

}

int main(void)
{
    // std::cout<<Recursion_fib(10)<<std::endl;
    // std::cout<<TailRecursion_fib(10)<<std::endl;
    Hanoi(10, 'A', 'B', 'C');
}