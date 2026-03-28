#include <iostream>
#include <stack>

std::stack<int> in;
std::stack<int> out;

void pop()
{
    if(out.empty())
    {
        while (!in.empty())
        {
            int temp = in.top();
            out.push(temp);
            in.pop();
        }
    }

    out.pop();
}

void push(int i)
{
    in.push(i);
}

int main()
{
    return 0;
}