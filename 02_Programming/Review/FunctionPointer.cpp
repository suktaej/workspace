#include <iostream>
#include <cstdio>
#include <functional>

int CallFunc()
{
    return 10;
}

void CallFunc2(int num)
{
    printf("%d",num);
}

void CallFunc3(int a, int b, float c, char d)
{
    printf("%c %f %d",d,c,a+b);
}

void FunctionPointer()
{
    int (*funcPtr)();
    void (*funcPtr2)(int);

    funcPtr = &CallFunc;
    funcPtr2 = &CallFunc2;

    (*funcPtr2)((*funcPtr)());
}

void STLFunction()
{
    std::function<int()> stdFunc;
    std::function<void(int)> stdFunc2;

    stdFunc = CallFunc;
    stdFunc2 = CallFunc2;

    std::function<int()> stdFunc3 = std::bind(CallFunc);
    std::function<void(int)> stdFunc4 = std::bind(CallFunc2,10);

    // 1. parameter 순서 변경 가능
    // 2. element 고정
    // 3. member function를 일반함수로 rename
    std::function<void(int,int,float,char)> stdFunc5 = std::bind(CallFunc3, std::placeholders::_2, std::placeholders::_1, 10.f, 'C');
    
    // 실제 bind보다 lamdba의 사용이 잦음
    std::function<int(int, int)> tempLambda = [](int a, int b) -> int
    { return a + b; };

    stdFunc2(stdFunc());
}

int main(void)
{
    STLFunction();
    return 0;
}