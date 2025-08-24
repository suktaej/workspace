#include "CPPVector.h"

int main()
{
	CVector<int>* vec = new CVector<int>;
	vec->push_back(10);
	vec->emplace_back(20);
	vec->pop_back();
	vec->push_back(30);
	vec->push_back(40);
	vec->push_back(50);
	vec->insert(1, 20);
	
	std::cout << vec->at(3) << std::endl;
	std::cout << vec->back() << std::endl;
	std::cout << vec->front() << std::endl;

	vec->PrintArray();

	delete vec;
}