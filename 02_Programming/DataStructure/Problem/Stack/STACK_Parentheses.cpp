#include "STACK_Commons.h"

bool IsValidParentheses(const std::string& exp)
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
            {
                std::cout<<"False"<<std::endl;
				return false;
            }

			char top = scope.top();
			scope.pop();

			if (it == '(' && top != ')' ||
				it == '{' && top != '}' ||
				it == '[' && top != ']' )
            {
                std::cout<<"False"<<std::endl;
                return false;
            }
            else 
            {
                std::cout<<"match: "<<it<<" pop: "<<top<<std::endl;
            }
		}
	}
    std::cout<<"True"<<std::endl;
    return true;
}