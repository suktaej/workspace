#include "CPPVector.h"
#include <utility>
#include <iostream>

template<typename T>
void CVector<T>::Resizing()
{
    // 현재 사이즈가 용량보다 작으면 리사이징 필요 없음
    if (mSize < mCapacity)
        return;

    // 용량이 0이면 초기 용량 1, 아니면 2배
    size_t newCapacity = (mCapacity == 0) ? 1 : mCapacity * 2;
    T* newArr = new T[newCapacity]; // 새로운 배열 할당

    for (size_t i = 0; i < mSize; ++i) 
    {
        /* 기존 코드
        std::move(mArr, mArr + mSize, newArr);
        // *(newArr + i) = *(arr + i);   // 복사 대입
        // newArr[i] = std::move(mArr[i]); // std::move로 소유권을 이전
        */

        // placement new와 std::move를 사용하여 기존 객체를 새 위치로 "이동 생성"
        new(&newArr[i]) T(std::move(mArr[i])); // T의 이동 생성자 호출
        // 기존 위치의 객체는 소멸자 호출
        // (T가 non-trivial 타입일 경우 필수. trivial 타입(int, float 등)은 생략 가능하나 안전을 위해 호출)
        mArr[i].~T();
    }

    delete[] mArr;      // 기존 배열 메모리 해제
    mArr = newArr;      // mArr이 새 배열을 가리키도록
    mCapacity = newCapacity; // 용량 갱신
}

template<typename T>
void CVector<T>::PrintArray()
{
    for (size_t i = 0; i < mSize; ++i)
        std::cout << *(mArr + i) << " ";
}

template<typename T>
void CVector<T>::push_back(const T& value)
{
    Resizing();

    *(mArr + mSize) = value;
    ++mSize;
}

template<typename T>
void CVector<T>::pop_back()
{
    if (0 == mSize)
        throw std::out_of_range("pop_back : zero size");

    --mSize;
    mArr[mSize].~T(); // 기존 타입(int, float..)이 아닌 동적할당 된 타입(std::string, class)이 존재할 경우 
    // 메모리 누수가 발생할 수 있음
}

template<typename T>        // 바깥 템플릿(컨테이너가 어떤 타입을 담을지 결정)
template <class... Args>    // 안쪽 템플릿(함수가 어떤 인자를 받아 T객체를 생성할 것인지 결정)

//Args... : 여러타입의 rvalue
//Args&&... : 여러타입의 lvalue
void CVector<T>::emplace_back(Args&&...args)
{
    Resizing();
    //Placement New : 이미 할당 된 메모리에 객체를 제자리에서 생성
    //Perfact Forwarding : 전달받은 인자들을 완벽하게 전달
    new(&mArr[mSize]) T(std::forward<Args>(args)...);
    ++mSize;
}

template<typename T>
template <class... Args>
CIterator<T> CVector<T>::emplace(size_t idx, Args&&...args)
{
    // 1. 인덱스 범위 체크 (0 <= idx <= size)
    if (idx > mSize)
        throw std::out_of_range("emplace: index out of range");

    // 2. 공간이 부족하면 리사이즈
    Resizing();

    // 3. idx 위치 이후의 요소들을 뒤로 한 칸씩 이동
    for (size_t i = mSize; i > idx; --i)
        mArr[i] = std::move(mArr[i - 1]);

    // 4. idx 위치에 객체를 "제자리 생성" (Perfect Forwarding)
    new(&mArr[idx]) T(std::forward<Args>(args)...);

    // 5. 요소 개수 증가
    ++mSize;

    // 6. 삽입된 위치를 가리키는 iterator 반환
    return CIterator<T>(&mArr[idx], mArr, mSize);
}

template<typename T>
CIterator<T> CVector<T>::insert(size_t idx, const T& value)
{
    if (idx > mSize)
        throw std::out_of_range("insert: index out of range");

    Resizing();

    for (size_t i = mSize; i > idx; --i)
        mArr[i] = std::move(mArr[i - 1]);

    mArr[idx] = value;
    ++mSize;

    return CIterator<T>(&mArr[idx], mArr, mSize);
}

template<typename T>
CIterator<T> CVector<T>::erase(size_t idx)
{
    if (mSize <= idx)
        throw std::out_of_range("erase: index out of range");

    for (size_t i = idx; i < mSize - 1; ++i)
        mArr[i] = std::move(mArr[i + 1]);

    // 크기를 줄이고 마지막 객체의 소멸자 호출
    pop_back();

    return CIterator<T>(mArr + idx, mArr, mSize);
}

template<typename T>
void CVector<T>::remove(const T& value)
{
    if (0 == mSize)
        return;

    for (size_t i = 0; i < mSize; ++i)
    {
        if (value == *(mArr + i))
        {
            erase(i);
            return;
        }
    }
}

template<typename T>
CIterator<T> CVector<T>::begin()
{
    return CIterator<T>(mArr, mArr, mSize);
}

template<typename T> CIterator<T> CVector<T>::end()
{
    return CIterator<T>(mArr + mSize, mArr, mSize);
}

template<typename T>
T& CVector<T>::at(size_t idx)
{
    if (idx >= mSize)
        throw std::out_of_range("at : index out of range");

    return *(mArr + idx);
}

template<typename T>
const T& CVector<T>::at(size_t idx) const
{
    if (idx >= mSize)
        throw std::out_of_range("at : index out of range");

    return *(mArr + idx);
}

template<typename T>
T& CVector<T>::front()
{
    if (0 == mSize)
        throw std::out_of_range("front : zero size");

    return *(mArr);
}

template<typename T>
const T& CVector<T>::front() const
{
    if (0 == mSize)
        throw std::out_of_range("front : zero size");

    return *(mArr);
}

template<typename T>
T& CVector<T>::back()
{
    if (0 == mSize)
        throw std::out_of_range("back : zero size");

    return *(mArr + mSize - 1);
}

template<typename T>
const T& CVector<T>::back() const
{
    if (0 == mSize)
        throw std::out_of_range("back : zero size");

    return *(mArr + mSize - 1);
}

template<typename T>
bool CVector<T>::contains(const T& value)
{
    for (size_t i = 0; i < mSize; ++i)
    {
        if (value == *(mArr + i))
            return true;
    }

    return false;
}

template<typename T> void CVector<T>::clear()
{
    for (size_t i = 0; i < mSize; ++i)
        mArr[i].~T();

    mSize = 0;
}

template<typename T>
void CVector<T>::reserve(size_t newCapacity)
{
    // 요청한 용량이 현재 용량보다 작거나 같으면 아무것도 하지 않음
    if (newCapacity <= mCapacity)
        return;

    T* newArr = new T[newCapacity];

    for (size_t i = 0; i < mSize; ++i)
        newArr[i] = std::move(mArr[i]);

    delete[] mArr;
    mArr = newArr;
    mCapacity = newCapacity;
}

template<typename T>
void CVector<T>::resize(size_t newSize)
{
    //값이 같다면 무시
    if (newSize == mSize)
        return;
    //받아온 size가 기존 size보다 크고
    else if (newSize > mSize)
    {
        //capacity보다 크다면 메모리 증량
        if (newSize > mCapacity)
            reserve(newSize);
        //새 공간을 기존 객체로 채움
        for (size_t i = mSize; i < newSize; ++i)
            // Placement New를 사용하여 메모리에 직접 객체 생성
            new(&mArr[i]) T();
    }
    //기존 값보다 작다면
    else if (newSize < mSize)
    {
        for (size_t i = newSize; i < mSize; ++i)
            mArr[i].~T();
    }
    // 마지막으로 실제 크기를 업데이트
    mSize = newSize;
}

template<typename T>
void CVector<T>::resize(size_t newSize, const T& init)
{
    if (newSize == mSize)
        return;
    
    else if (newSize > mSize)
    {
        if (newSize > mCapacity)
            reserve(newSize);

        for (size_t i = mSize; i < newSize; ++i)
            new(&mArr[i]) T(init);  // const T&를 복사
    }
    else
    {
        for (size_t i = newSize; i < mSize; ++i)
            mArr[i].~T();
    }

    mSize = newSize;
}