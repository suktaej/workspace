#include <iostream>
#include <algorithm>
#include <string>

bool isNumber(std::string token)
{
    for(char c : token)
        if (c < '0' || c > '9')
            return false;

    return true;
}

int revNumber(std::string token)
{
    int res = 0;
    int size = token.size();
    for (int i = size-1; i >= 0; --i)
        res = (res * 10) + (token[i] - '0');

    return res;
}

int revInt(int token)
{
    int res = 0;
    while(token > 0)
    {
        res = res * 10 + (token % 10);
        token /= 10;
    }

    return res;
}

int main()
{
    int op1, op2;
    char opcode;

    std::cin>>op1>>opcode>>op2;
    op1 = revInt(op1);
    op2 = revInt(op2);
    std::cout<<revInt(op1+op2);
    
    return 0;
}