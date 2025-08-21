#include "CPPVector.h"
#include "CPPIterator.h"

void CVector::Resizing()
{
	if (size < capacity)
		return;
	
	int newCapacity = (capacity == 0) ? 1 : capacity * 2;
	int* newArr = new int[newCapacity];

	for (int i = 0; i < size; ++i)
		*(newArr + i) = *(arr + i);

	delete[] arr;
	arr = newArr;
	capacity = newCapacity;
}

void CVector::PrintArray()
{
	for (int i = 0; i < size; ++i)
		std::cout << *(arr + i) << " ";
}

void CVector::push_back(int value)
{
	Resizing();

	*(arr + size) = value;
	++size;
}

void CVector::pop_back()
{
	if (0 == size)
		return;

	--size;
}
