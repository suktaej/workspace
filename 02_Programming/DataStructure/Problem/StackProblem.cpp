#include <cstring>
#include <stack>
#include <iostream>
#include <sstream>

namespace StringUtils
{
	bool isNumber(const std::string& token);
	bool isOperator(const std::string& token);
}

namespace StackProblems
{
	void ReverseOutput(const std::string& src);
	bool IsValidParentheses(const std::string& exp);
	int EvaluatePostfix(const std::string& exp);
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
	std::string InfixToPostfix(const std::string& exp);
    ExprNode* buildFromPostfix(const std::string& exp);
	ExprNode* buildFromPrefix(const std::string& exp);
	ExprNode* recursivePrefix(std::istringstream& iss);
	int Evaluate(ExprNode* root);
    void Inorder(ExprNode* root);
    void Postorder(ExprNode* root);
}

int main()
{
	using namespace StackProblems;
	using namespace ExpressionTree;

	int maze[16][16] = 
	{ // row 0
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,2,1,1,1,0,1,1,1,0,1,0,1,1,1,0},
{0,0,0,1,0,0,1,0,1,0,1,0,0,0,1,0},
{0,1,1,1,1,1,1,0,1,1,1,1,1,0,1,0},
{0,1,0,0,0,0,1,0,0,0,0,0,1,0,1,0},
{0,1,1,1,1,0,1,1,1,1,1,0,1,1,1,0},
{0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0},
{0,1,1,0,1,1,1,1,1,0,1,1,1,0,1,0},
{0,1,0,0,0,0,0,0,1,0,0,0,1,0,1,0},
{0,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0},
{0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0},
{0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,0},
{0,1,0,0,1,0,0,0,1,0,0,0,1,0,1,0},
{0,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0},
{0,0,1,0,0,0,1,0,0,0,1,0,0,0,3,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

	// ReverseOutput("HelloWorld!");
	// std::cout<<(IsValidParentheses("f+{a+b*(c-d)/}") ? "True" : "False")<<std::endl;
	// std::cout<<EvaluatePostfix("10 2 8 + * 50 -")<<std::endl;

	std::string infixExp = "10 * 20 + ( 5 / 10 - 2 )";
	std::string postfixExp = InfixToPostfix(infixExp);
	ExprNode* root = buildFromPostfix(postfixExp);
	std::cout << "\nResult: " << Evaluate(root) <<"\n";

	return 0;
}

bool StringUtils::isNumber(const std::string& token)
{
    for (char c : token)
        if (!isdigit(c))
            return false;
    return true;
}

inline bool StringUtils::isOperator(const std::string& token)
{
    return token == "+" || token == "-" || token == "*" || token == "/";
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
		if(StringUtils::isNumber(token))
		{
			stk.push(std::stoi(token));
		}
		else if (StringUtils::isOperator(token))
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

inline ExprNode* ExpressionTree::recursivePrefix(std::istringstream& iss)
{
    std::string token;

    if (!(iss >> token))
        return nullptr;

    ExprNode* node = new ExprNode(token);

    if (StringUtils::isOperator(token)) {
        node->left = recursivePrefix(iss);
        node->right = recursivePrefix(iss);
    }

    return node;
}

inline ExprNode* ExpressionTree::buildFromPrefix(const std::string& exp)
{
    std::istringstream iss(exp);
    return recursivePrefix(iss);
}

inline ExprNode* ExpressionTree::buildFromPostfix(const std::string &exp)
{
    std::istringstream iss(exp);
    std::string token;
    std::stack<ExprNode*> stk;

    while(iss>>token)
    {
        if(!StringUtils::isOperator(token))
            stk.push(new ExprNode(token));
        else
        {
			ExprNode* operNode = new ExprNode(token);

            operNode->right = stk.top();
            stk.pop();
            operNode->left = stk.top();
            stk.pop();

            stk.push(operNode);
        }
    }
    return stk.top();       // root node
}

inline void ExpressionTree::Inorder(ExprNode* root)
{
    if(!root)
        return;

    if(StringUtils::isOperator(root->value))
        std::cout<<"( ";

	Inorder(root->left);
	std::cout<<root->value<<" ";
	Inorder(root->right);

	if(StringUtils::isOperator(root->value))
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

    if (!StringUtils::isOperator(root->value)) 
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

inline std::string ExpressionTree::InfixToPostfix(const std::string& exp)
{
	using namespace StackProblems;

    std::istringstream iss(exp);
    std::string token;
    std::stack<std::string> opStack;
    std::ostringstream output;

    auto precedence = [](const std::string& op) 
	{
        if (op == "+" || op == "-") 
			return 1;
        if (op == "*" || op == "/") 
			return 2;

        return 0;
    };

    while (iss >> token)
    {
        
		if(StringUtils::isNumber(token)) // if (!isOperator(token) && token != "(" && token != ")")
        {
            output << token << " ";
        }
		else if (token == "(")
        {
            opStack.push(token);
        }
		else if (token == ")")
        {
            while (!opStack.empty() && opStack.top() != "(")
            {
                output << opStack.top() << " ";
                opStack.pop();
            }

            opStack.pop(); // '(' 제거
        }
		else // Operator
        {
            while (!opStack.empty() && precedence(opStack.top()) >= precedence(token)) // Stack에서 연산자 우선순위는 별도로 확인
            {
                output << opStack.top() << " ";
                opStack.pop();
            }

            opStack.push(token);
        }
    }

    // 남은 연산자 처리
    while (!opStack.empty())
    {
        output << opStack.top() << " ";
        opStack.pop();
    }

    return output.str();
}