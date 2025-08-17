#pragma once

#include <iostream>

class Vector
{
public:
	// Constructor
	Vector() : size(0), capacity(4)
	{
		arr = new int[4] {};
	}
	Vector(int _cap) : size(0), capacity(_cap)
	{
		arr = new int[_cap] {};
	}
	Vector(int* _arr, int _size) : size(_size), capacity(_size)
	{
		arr = new int[_size];
		
		for (int i = 0; i < _size; ++i)
			*(arr + i) = *(_arr + i);
	}
	// Copy
	Vector(const Vector& vec) : size(vec.size), capacity(vec.capacity)
	{
		arr = new int[size];

		for (int i = 0; i < size; ++i)
			*(arr + i) = *(vec.arr + i);
	}
	// CopyAssignment
	Vector& operator=(const Vector& vec)
	{
		if (this != &vec)
		{
			delete[] arr;
			size = vec.size;
			capacity = vec.capacity;

			arr = new int[size];

			for (int i = 0; i < size; ++i)
				*(arr + i) = *(vec.arr + i);
		}
		// 현재 객체를 참조로 반환
		return *this;
	}
	// Move
	// 원본(인자값)의 소유권 이동 후 변경이 필요하므로 const 불가
	// &&은 non-const rvalue refrence
	Vector(Vector&& vec) noexcept
		: arr(vec.arr), size(vec.size), capacity(vec.capacity)
	{
		vec.arr = nullptr;
		vec.size = 0;
		vec.capacity = 0;
	}
	// MoveAssignment
	Vector& operator=(Vector&& vec) noexcept
	{
		if (this != &vec)
		{
			delete[] arr;

			arr = vec.arr;
			size = vec.size;
			capacity = vec.capacity;

			vec.arr = nullptr;
			vec.size = 0;
			vec.capacity = 0;
		}
		return *this;
	}
	// Destructor
	~Vector()
	{
		delete[] arr;
	}

private:
	int* arr;
	int size;
	int capacity;

public:
	void Resizing();
	void PrintArray();

	void arr_pushback(int value);
	void arr_popback();
	void arr_insert(int idx, int value);
	//void arr_emplace(int idx, int value);

	void arr_erase(int idx);
	void arr_remove(int value);
	void arr_clear();

	int arr_at(int idx);
	int* arr_begin();
	int* arr_end();

	int arr_front();
	int arr_back();

	int arr_find(int value);   
	bool arr_contains(int value); 
};
