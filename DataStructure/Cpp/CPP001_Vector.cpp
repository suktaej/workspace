#include "CPP001_Vector.h"

void Vector::Resizing()
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

void Vector::PrintArray()
{
	for (int i = 0; i < size; ++i)
		std::cout << *(arr + i) << " ";
}

void Vector::arr_pushback(int value)
{
	Resizing();

	*(arr + size) = value;
	++size;
}

void Vector::arr_popback()
{
	if (0 == size)
		return;

	--size;
}

void Vector::arr_insert(int idx, int value)
{
}

void Vector::arr_emplace(int idx, int value)
{
}

void Vector::arr_erase(int idx)
{
}

void Vector::arr_remove(int value)
{
}

void Vector::arr_clear()
{
}

int Vector::arr_at(int idx)
{
	return 0;
}

int* Vector::arr_begin()
{
	return nullptr;
}

int* Vector::arr_end()
{
	return nullptr;
}

int Vector::arr_front()
{
	return 0;
}

int Vector::arr_back()
{
	return 0;
}

int Vector::arr_find(int value)
{
	return 0;
}

bool Vector::arr_contains(int value)
{
	return false;
}
