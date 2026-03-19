#include <iostream>
#include <stack>
#include <string>
#include <vector>

std::string tree[128] = {};

int parent(int i) { return (i - 1) / 2; }
int left(int i)   { return 2 * i + 1; }
int right(int i)  { return 2 * i + 2; }

void inOrder(int i)
{
    int ts = sizeof(tree)/sizeof(tree[0]);
    
    if(i >= ts)
        return;

    inOrder(left(i));
    std::cout<<tree[i];
    inOrder(right(i));
}

std::stack<int> operend;

void postCal(int i)
{
    std::string c = tree[i];
    if(c == "+" || c == "-" || c == "*" || c == "/" || c == "%")
    {
        int rightValue = operend.top();
        operend.pop();
        int leftValue = operend.top();
        operend.pop();

        if(c == "+") operend.push(leftValue + rightValue);
        else if(c == "-") operend.push(leftValue - rightValue);
        else if(c == "*") operend.push(leftValue * rightValue);
        else if(c == "/") operend.push(leftValue / rightValue);
        else if(c == "%") operend.push(leftValue % rightValue);
    }
    else
        operend.push(std::stoi(c));
}

void postOrder(int i)
{
    int ts = sizeof(tree)/sizeof(tree[0]);
    
    if(i >= ts)
        return;

    postOrder(left(i));
    postOrder(right(i));
    postCal(i);
}

int preCal(int i)
{
    if(i>=128 || tree[i]=="")
        return 0;

    std::string c = tree[i];
    if(c == "+" || c == "-" || c == "*" || c == "/" || c == "%")
    {
        int leftVal = preCal(left(i));
        int rightVal = preCal(right(i));

        if (c == "+") return leftVal + rightVal;
        if (c == "-") return leftVal - rightVal;
        if (c == "*") return leftVal * rightVal;
        if (c == "/") return leftVal / rightVal;
        if (c == "%") return leftVal % rightVal;
    }
    else
        return std::stoi(c);
}

void preOrder(int i)
{
    int ts = sizeof(tree)/sizeof(tree[0]);
    
    if(i >= ts)
        return;

    std::cout<<tree[i];
    preOrder(left(i));
    preOrder(right(i));
}

int main()
{
    return 0;
}