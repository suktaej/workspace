#pragma once
#include <cstddef> //size_t

template<typename T>
class CIterator
{
private:
	T* m_ptr;		// 현재 위치 포인터
	T* m_begin;		// 컨테이너 시작 포인터
	size_t m_size;	// 컨테이너 크기

public:
	// Constructor
	CIterator(T* _ptr = nullptr,T* _begin = nullptr, size_t _size = 0) 
		: m_ptr(_ptr), m_begin(_begin), m_size(_size) {}

	// Pointer
	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }

	CIterator& operator++()
	{
		++m_ptr;
		return *this;
	}

	CIterator operator++(int)
	{
		CIterator temp = *this;
		++(*this);
		return temp;
	}

	CIterator& operator--()
	{
		--m_ptr;
		return *this;
	}

	CIterator operator--(int)
	{
		CIterator temp = *this;
		--(*this);
		return temp;
	}
	
	bool operator==(const CIterator& iter) const { return m_ptr == iter.m_ptr; }
	bool operator!=(const CIterator& iter) const { return m_ptr != iter.m_ptr; }

	T& operator[](const size_t value) const { return *(m_ptr + value); }
	
	CIterator operator+(size_t value) const { return CIterator(m_ptr + value, m_begin, m_size); }
	CIterator operator-(size_t value) const { return CIterator(m_ptr - value, m_begin, m_size); }
	ptrdiff_t operator-(const CIterator& other) const { return m_ptr - other.m_ptr; }

	bool operator<(const CIterator& other) const { return m_ptr < other.m_ptr; }
	bool operator>(const CIterator& other) const { return m_ptr > other.m_ptr; }
	bool operator<=(const CIterator& other) const { return m_ptr <= other.m_ptr; }
	bool operator>=(const CIterator& other) const { return m_ptr >= other.m_ptr; }
};
