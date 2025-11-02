#include <cstring>
#include <stack>
#include <iostream>
#include <sstream>

namespace StackProblems
{
	void ReverseOutput(const std::string& src);
	bool IsValidParentheses(const std::string& exp);
	int EvaluatePostfix(const std::string& exp);
	bool isNumber(const std::string& token);
}

struct ExprNode
{
    std::string value;
    ExprNode* left;
    ExprNode* right;

    ExprNode(std::string val)
    : value(std::move(val)), left(nullptr), right(nullptr) {}
};

namespace ExpressionTree
{
    ExprNode* buildFromPostfix(const std::string& exp);
    void Inorder(ExprNode* root);
    void Postorder(ExprNode* root);
    int Evaluate(ExprNode* root);
    bool isOperator(const std::string& token);
}

int main()
{
	using namespace StackProblems;
	using namespace ExpressionTree;

	// ReverseOutput("HelloWorld!");
	// std::cout<<(IsValidParentheses("f+{a+b*(c-d)/}") ? "True" : "False")<<std::endl;
	// std::cout<<EvaluatePostfix("10 2 8 + * 50 -")<<std::endl;

	std::string postfix = "3 4 + 5 *";
	ExprNode* root = buildFromPostfix(postfix);
	
    std::cout << "Inorder: ";
	Inorder(root);
	std::cout << "\nPostorder: ";
	Postorder(root);
	std::cout << "\nResult: " << Evaluate(root) <<"\n";

	return 0;
}

inline void StackProblems::ReverseOutput(const std::string& src)
{
	std::stack<char> stk;

	for (auto it : src)
	{
		stk.push(it);
	}

	while (!stk.empty())
	{
		std::cout << stk.top();
		stk.pop();
	}
	std::cout<<"\n";
}

inline bool StackProblems::IsValidParentheses(const std::string& exp)
{
	std::stack<char> scope;

	for (const char it : exp)
	{
		if (it == '(' || it == '{' || it == '[' )
        {
            std::cout<<"push: "<<it<<std::endl;
			scope.push(it);
        }
		else if (it == ')' || it == '}' || it == ']')
		{
			if (scope.empty())
 				return false;

			char top = scope.top();
			scope.pop();

			if ((it == ')' && top != '(') ||
				(it == '}' && top != '{') ||
				(it == ']' && top != '[')) 
			{
				return false;
			} 
			else 
			{
				std::cout << "match: " << it << " pop: " << top << std::endl;
			}
		}
	}
    return true;
}

inline int StackProblems::EvaluatePostfix(const std::string& exp)
{
	std::stack<int> stk;
	std::istringstream iss(exp);
	std::string token;

	while (iss >> token)	// stream input operator
	{
		//if (isdigit(token[0]))  // int isdigit(int ch) 하나의 문자에 대해서만 검사
		if(isNumber(token))
		{
			stk.push(std::stoi(token));
		}
		else if (token == "+" || token == "-" || token == "*" || token == "/")
		{
			if (stk.size() < 2)
				throw std::runtime_error("Invalid postfix expression");

			int b = stk.top(); 
			stk.pop();
			int a = stk.top(); 
			stk.pop();

			if (token == "+") 
				stk.push(a + b);
			else if (token == "-") 
				stk.push(a - b);
			else if (token == "*") 
				stk.push(a * b);
			else if (token == "/") 
				stk.push(a / b);
		}
	}

	return stk.empty() ? 0 : stk.top();
}

bool StackProblems::isNumber(const std::string& token)
{
    for (char c : token)
        if (!isdigit(c))
            return false;
    return true;
}

inline ExprNode* ExpressionTree::buildFromPostfix(const std::string &exp)
{
    std::istringstream iss(exp);
    std::string token;
    std::stack<ExprNode*> stk;

    while(iss>>token)
    {
        if(!isOperator(token))
            stk.push(new ExprNode(token));
        else
        {
            ExprNode* right = stk.top();
            stk.pop();
            ExprNode* left = stk.top();
            stk.pop();
            ExprNode* operNode = new ExprNode(token);
            operNode->left = left;
            operNode->right = right;
            stk.push(operNode);
        }
    }
    return stk.top();       // root node
}

inline void ExpressionTree::Inorder(ExprNode* root)
{
    if(!root)
        return;

    if(isOperator(root->value))
        std::cout<<"( ";

	Inorder(root->left);
	std::cout<<root->value<<" ";
	Inorder(root->right);

	if(isOperator(root->value))
		std::cout<<") ";
}

inline void ExpressionTree::Postorder(ExprNode* root)
{
    if (!root) 
        return;

    Postorder(root->left);
    Postorder(root->right);
    std::cout << root->value << " ";
}

inline int ExpressionTree::Evaluate(ExprNode* root)
{
    if (!root)
        return 0;

    if (!isOperator(root->value)) 
        return std::stoi(root->value);

    int left = Evaluate(root->left);
    int right = Evaluate(root->right);

    if (root->value == "+") 
        return left + right;
    if (root->value == "-") 
        return left - right;
    if (root->value == "*") 
        return left * right;
    if (root->value == "/") 
        return left / right;

    return 0;
}

inline bool ExpressionTree::isOperator(const std::string& token)
{
    return token == "+" || token == "-" || token == "*" || token == "/";
}

