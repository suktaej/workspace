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

#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <map>

struct Node 
{
    std::string data;
    Node *left, *right;
    Node(std::string s) : data(s), left(nullptr), right(nullptr) {}
    Node(char c) : data(1, c), left(nullptr), right(nullptr) {}
};

int getPriority(char op) 
{
    if (op == '+' || op == '-') 
        return 1;
    if (op == '*' || op == '/' || op == '%') 
        return 2;
    if (op == '(') 
        return 0;

    return -1;
}

std::stack<char> opcodes;
std::stack<Node*> operNodes;

void buildSubTree() 
{
    if (operNodes.size() < 2) 
        return;
    
    char op = opcodes.top(); opcodes.pop();
    Node* val2 = operNodes.top(); operNodes.pop();
    Node* val1 = operNodes.top(); operNodes.pop();
    
    Node* newNode = new Node(op);
    newNode->left = val1;
    newNode->right = val2;
    operNodes.push(newNode);
}

void makeTree() 
{
    std::string s = "1 + 4 * 2";
    std::stringstream iss(s);
    std::string token;

    while(iss >> token) 
    {
        if (token == "(") 
            opcodes.push('(');
        else if (token == ")") 
        {
            while (!opcodes.empty() && opcodes.top() != '(') 
                buildSubTree();
            
            opcodes.pop(); 
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/") 
        {
            char currentOp = token[0];

            while (!opcodes.empty() &&
                   getPriority(opcodes.top()) >= getPriority(currentOp))
                buildSubTree();

            opcodes.push(currentOp);
        }
        else
            operNodes.push(new Node(token));
    }

    while(!opcodes.empty()) 
        buildSubTree();
}

int main()
{
    return 0;
}