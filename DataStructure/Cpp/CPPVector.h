#pragma once

#include <iostream>

class CVector
{
public:
	// Constructor
	CVector() : size(0), capacity(4)
	{
		arr = new int[4] {};
	}
	CVector(int _cap) : size(0), capacity(_cap)
	{
		arr = new int[_cap] {};
	}
	CVector(int* _arr, int _size) : size(_size), capacity(_size)
	{
		arr = new int[_size];
		
		for (int i = 0; i < _size; ++i)
			*(arr + i) = *(_arr + i);
	}
	// Copy
	CVector(const CVector& vec) : size(vec.size), capacity(vec.capacity)
	{
		arr = new int[size];

		for (int i = 0; i < size; ++i)
			*(arr + i) = *(vec.arr + i);
	}
	// CopyAssignment
	CVector& operator=(const CVector& vec)
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
	CVector(CVector&& vec) noexcept
		: arr(vec.arr), size(vec.size), capacity(vec.capacity)
	{
		vec.arr = nullptr;
		vec.size = 0;
		vec.capacity = 0;
	}
	// MoveAssignment
	CVector& operator=(CVector&& vec) noexcept
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
	~CVector()
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

	void push_back(int value);
	void emplace_back(int idx, int value);
	void pop_back();
	void insert(int idx, int value);

	void erase(int idx);
	void remove(int value);
	void clear();

	int at(int idx);
	class CIterator& begin();
	class CIterator& end();

	int front();
	int back();

	int find(int value);   
	bool contains(int value); 
};
