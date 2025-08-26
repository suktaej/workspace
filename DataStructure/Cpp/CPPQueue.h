#pragma once
#include "CPPList.h"

template<typename T>
class CQueue
{
public:
    CQueue() = default;
    CQueue(std::initializer_list<T> items)
    {
        for (const T& item : items)
            mList.push_back(item);
    }

private:
    CList<T> mList;

public:
    void enqueue(const T& value) { mList.push_back(value); }  
    void dequeue() { mList.pop_front(); }
    T& front() { return mList.front(); }
    const T& front() const { return mList.front(); }
    T& back() { return mList.back(); }  
    const T& back() const { return mList.back(); }
    bool empty() const { return mList.empty(); }
    size_t size() const { return mList.size(); }
};
