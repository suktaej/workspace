#pragma once
#include "CPPList.h"
#include "CPPVector.h"

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

template<typename T>
class CCircuitQueue {
public:
    explicit CCircuitQueue(size_t cap)
        : mCapacity(cap), mArr(new T[cap]), mFront(0), mRear(0), mSize(0) { }
    CCircuitQueue(const CCircuitQueue& queue)
        : mCapacity(queue.mCapacity), mFront(queue.mFront), mRear(queue.mRear), mSize(queue.mSize)
    {
        mArr = new T[queue.mCapacity];

        for (int i = 0; i < queue.mSize; ++i)
            mArr[i] = queue.mArr[(queue.mFront + i) % queue.mCapacity];
    }
    CCircuitQueue& operator=(const CCircuitQueue& queue)
    {
        if (this != &queue)
        {
            mSize = queue.mSize;
            mCapacity = queue.mCapacity;
            mFront = queue.mFront;
            mRear = queue.mRear;
            
            delete[] mArr;
            mArr = new T[mCapacity];

            for (int i = 0; i < queue.mSize; ++i)
                mArr[i] = queue.mArr[(queue.mFront + i) % queue.mCapacity];
        }
        return *this;
    }
    CCircuitQueue(CCircuitQueue&& queue) noexcept
        : mArr(queue.mArr), mSize(queue.mSize), mCapacity(queue.mCapacity), mFront(queue.mFront), mRear(queue.mRear)
    {
        queue.mArr = nullptr;
        queue.mSize = 0;
        queue.mCapacity = 0;
        queue.mFront = 0;
        queue.mRear = 0;
    }
    CCircuitQueue& operator=(CCircuitQueue&& queue) noexcept
    {
        if(this != &queue)
        { 
            mSize = queue.mSize;
            mCapacity = queue.mCapacity;
            mFront = queue.mFront;
            mRear = queue.mRear;

            delete[] mArr;
            mArr = new T[mCapacity];

            for (int i = 0; i < queue.mSize; ++i)
                mArr[i] = queue.mArr[i];

            queue.mArr = nullptr;
            queue.mSize = 0;
            queue.mCapacity = 0;
            queue.mFront = 0;
            queue.mRear = 0;
        }
        return *this;
    }
    ~CCircuitQueue() { delete[] mArr; }

private:
    T* mArr;
    size_t mCapacity;
    size_t mSize;
    size_t mFront;
    size_t mRear;

public:
    bool empty() const { return mSize == 0; }
    bool full() const { return mSize == mCapacity; }
    size_t size() const { return mSize; }

    void enqueue(const T& value)
    {
        if(true == full())
            throw std::overflow_error("Queue is full");

        mArr[mRear] = value;
        mRear = (mRear + 1) % mCapacity;

        ++mSize;
    }

    void dequeue()
    {
        if (true == empty()) 
            throw std::underflow_error("Queue is empty");

        mFront = (mFront + 1) % mCapacity;
        --mSize;
    }

    T& front() {

        if (true == empty())
            throw std::underflow_error("Queue is empty");

        return mArr[mFront];
    }
};

// HeapTree
template<typename T>
class CPriorityQueue
{
public:
    CPriorityQueue() = default;
    CPriorityQueue(std::initializer_list<T> items)
    {
        for (const T& it : items)
            push(it);
    }
private:
    CVector<T> mHeap;

public:
    // 0-indexed
    int Parent(int i) { return (i - 1) / 2; }
    int LChild(int i) { return 2 * i + 1; }
    int RChild(int i) { return 2 * i + 2; }

    // 1-indexed
    //int Parent(int i) { return i / 2; }
    //int LChild(int i) { return 2 * i ; }
    //int RChild(int i) { return 2 * i + 1; }

    void HeapifyUp(int idx)
    {
        while (idx != 0 && mHeap[Parent(idx)] < mHeap[idx])
        {
            std::swap(mHeap[Parent(idx)], mHeap[idx]);
            idx = Parent(idx);
        }
    }

    void HeapifyDown(int idx)
    {
        int largestIdx = idx;
        int left = LChild(idx);
        int right = RChild(idx);

        if (left < mHeap.size() && mHeap[left] > mHeap[largestIdx])
            largestIdx = left;
        if (right < mHeap.size() && mHeap[right] > mHeap[largestIdx])
            largestIdx = right;

        if (largestIdx != idx)
        {
            std::swap(mHeap[idx], mHeap[largestIdx]);
            HeapifyDown(largestIdx);
        }
    }

    void push(const T& value)
    {
        mHeap.push_back(value);
        HeapifyUp((int)mHeap.size()-1);
    }

    void pop()
    {
        if (true == mHeap.empty())
            throw std::out_of_range("Heap is empty");

        mHeap[0] = mHeap.back();
        mHeap.pop_back();

        if (false == mHeap.empty())
            HeapifyDown(0);
    }

    int top() const
    {
        if (true == mHeap.empty())
            throw std::out_of_range("Heap is empty");

        return mHeap[0];
    }

    void PrintHeap() const
    {
        for (size_t i=0 ; i< mHeap.size(); ++i)
            std::cout << mHeap[i] << " ";
        std::cout << "\n";
    }
};
