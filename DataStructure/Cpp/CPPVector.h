#pragma once

#include "CPPIterator.h"

template<typename T>
class CVector
{
public:
	// Constructor
	CVector() : size(0), capacity(4)
	{
		arr = new T[4] {};
	}
	CVector(size_t _cap) : size(0), capacity(_cap)
	{
		arr = new T[_cap] {};
	}
	CVector(size_t* _arr, size_t _size) : size(_size), capacity(_size)
	{
		arr = new T[_size];
		
		for (size_t i = 0; i < _size; ++i)
			*(arr + i) = *(_arr + i);
	}
	// Copy
	CVector(const CVector& vec) : size(vec.size), capacity(vec.capacity)
	{
		arr = new T[capacity];

		for (size_t i = 0; i < size; ++i)
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

			arr = new T[capacity];

			for (size_t i = 0; i < size; ++i)
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
	T* arr;
	size_t size;
	size_t capacity;

public:
	void Resizing();
	void PrintArray();

	void push_back(const T& value);
	// Template Parameter Pack
	// Args라는 이름으로 여러 타입을 받을 수 있음
	template <class... Args>
	// Args타입 값들을 Perfact forwarding으로 받음
	// 함수호출 시 인자의 개수와 타입의 수에 구애받지 않음
	void emplace_back(Args &&...args);
	void pop_back();
	CIterator<T> insert(size_t idx, const T& value);
	template <class... Args>
    CIterator<T> emplace(size_t idx, Args&&... args);
	CIterator<T> erase(size_t idx);
	void vdelete(const T& value);
	// void remove(const T& value);
	void clear();

	CIterator<T> begin();
	CIterator<T> end();
	
	T& at(size_t idx);
	const T& at(size_t idx) const;
	T& front();
	const T& front() const;
	T& back();
	const T& back() const;

	bool contains(const T& value); 
};

#include "CPPVector.inl"