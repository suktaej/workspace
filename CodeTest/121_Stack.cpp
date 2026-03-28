#include <iostream>
#include <vector>
#include <stack>

std::vector<int> arr;
std::vector<char> res;
int n;

void stack()
{
	std::stack<int> s;
	int idx = 1;

	for(int i=0; i<n; ++i)
	{
		int target = arr[i];

		while(idx <= target)
		{
			s.push(idx);
			res.push_back('+');
			++idx;
		}
	
    if(!s.empty() && 
       s.top()==target)
		{
		    s.pop();
		    res.push_back('-');
		}
		else
		{
		    std::cout<<"NO";
		    return;
		}
	}
	
	for(const char& c : res)
	    std::cout<<c<<'\n';
}

int main()
{
	std::cin>>n;
	arr.resize(n);
	for(int i=0; i<n; ++i)
		std::cin>>arr[i];
	stack();

	return 0;
}