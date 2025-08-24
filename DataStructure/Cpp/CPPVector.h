#pragma once

#include "CPPIterator.h"

template<typename T>
class CVector
{
public:
	// Constructor
	CVector() : mSize(0), mCapacity(4)
	{
		mArr = new T[4]{};
	}
	CVector(size_t _cap) : mSize(0), mCapacity(_cap)
	{
		mArr = new T[_cap]{};
	}
	CVector(const T* _arr, size_t _size) : mSize(_size), mCapacity(_size)
	{
		mArr = new T[_size];

		for (size_t i = 0; i < _size; ++i)
			*(mArr + i) = *(_arr + i);
	}
	// Copy
	CVector(const CVector& vec) : mSize(vec.mSize), mCapacity(vec.mCapacity)
	{
		mArr = new T[mCapacity];

		for (size_t i = 0; i < mSize; ++i)
			*(mArr + i) = *(vec.mArr + i);
	}
	// CopyAssignment
	CVector& operator=(const CVector& vec)
	{
		if (this != &vec)
		{
			delete[] mArr;
			mSize = vec.mSize;
			mCapacity = vec.mCapacity;

			mArr = new T[mCapacity];

			for (size_t i = 0; i < mSize; ++i)
				*(mArr + i) = *(vec.mArr + i);
		}
		// 현재 객체를 참조로 반환
		return *this;
	}
	// Move
	// 원본(인자값)의 소유권 이동 후 변경이 필요하므로 const 불가
	// &&은 non-const rvalue refrence
	CVector(CVector&& vec) noexcept
		: mArr(vec.mArr), mSize(vec.mSize), mCapacity(vec.mCapacity)
	{
		vec.mArr = nullptr;
		vec.mSize = 0;
		vec.mCapacity = 0;
	}
	// MoveAssignment
	CVector& operator=(CVector&& vec) noexcept
	{
		if (this != &vec)
		{
			delete[] mArr;

			mArr = vec.mArr;
			mSize = vec.mSize;
			mCapacity = vec.mCapacity;

			vec.mArr = nullptr;
			vec.mSize = 0;
			vec.mCapacity = 0;
		}
		return *this;
	}
	// Destructor
	~CVector()
	{
		delete[] mArr;
	}

private:
	T* mArr;
	size_t mSize;
	size_t mCapacity;

public:
	void Resizing();
	void PrintArray();

	void reserve(size_t _capacity);
	void resize(size_t _size);

	void push_back(const T& value);
	// Template Parameter Pack
	// Args라는 이름으로 여러 타입을 받을 수 있음
	template <class... Args>
	// Args타입 값들을 Perfact forwarding으로 받음
	// 함수호출 시 인자의 개수와 타입의 수에 구애받지 않음
	void emplace_back(Args &&...args);
	template <class... Args>
	CIterator<T> emplace(size_t idx, Args&&... args);
	CIterator<T> insert(size_t idx, const T& value);

	void pop_back();
	CIterator<T> erase(size_t idx);

	// 범위검사 없음
	T& operator[](size_t idx)	
	{
		return mArr[idx];
	}

	const T& operator[](size_t idx) const
	{
		return mArr[idx];
	}

	void remove(const T& value);
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

	size_t size() { return mSize; }
	bool empty() { return mSize == 0; }
};

#include "CPPVector.inl"