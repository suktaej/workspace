#pragma once
#include "CPPList.h"

// CStack은 CList를 소유하는 관계(has-a)
// CStack의 기능은 CList의 기능을 재포장하여 제한된 인터페이스로 제공하는 Adapter 역할
// CStack의 자원관리는 CList로 위임(delegate)
template<typename T>
class CStack
{
public:
	CStack() = default;
	CStack(std::initializer_list<T> args)
	{
		for (const T& i : args)
			mList.push_back(i);
	}
	/*
	CStack(const CStack& stack) = default;
	CStack& operator=(const CStack stack) = default;
	CStack(CStack&& stack) noexcept = default;
	CStack& operator=(CStack&& stack) noexcept = default;
	~CStack() = default;
	*/

private:
	CList<T> mList;

public:
	void push(const T& value) { mList.push_back(value); }
	void pop() { mList.pop_back(); }
	T& top() { return mList.back(); }
	bool empty() const { return mList.empty(); }
	size_t size() const { return mList.size(); }
	void clear() { mList.clear(); }
};
