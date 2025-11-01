#include "STACK_Commons.h"

void ReverseOutput(const std::string& src)
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