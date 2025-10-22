#pragma once
#include "CPPList.h"

template<typename T>
class CDeque
{
public:
    CDeque() = default;
    CDeque(std::initializer_list<T> items)
    {
        for (const T& item : items)
            mList.push_back(item);
    }

private:
    CList<T> mList;

public:
    void push_front(const T& value) { mList.push_front(value); }
    void push_back(const T& value) { mList.push_back(value); }

    void pop_front() { mList.pop_front(); }
    void pop_back() { mList.pop_back(); }

    T& front() { return mList.front(); }
    const T& front() const { return mList.front(); }
    T& back() { return mList.back(); }
    const T& back() const { return mList.back(); }

    bool empty() const { return mList.empty(); }
    size_t size() const { return mList.size(); }
    void clear() { mList.clear(); }
};
