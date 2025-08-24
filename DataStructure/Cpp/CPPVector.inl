#include "CPPVector.h"
#include <utility>

template<typename T>
void CVector<T>::Resizing()
{
	if (size < capacity)
		return;
	
	size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
	T* newArr = new T[newCapacity];

	for (size_t i = 0; i < size; ++i)
		*(newArr + i) = *(arr + i);

	delete[] arr;
	arr = newArr;
	capacity = newCapacity;
}

template<typename T>
void CVector<T>::PrintArray()
{
	for (size_t i = 0; i < size; ++i)
		std::cout << *(arr + i) << " ";
}

template<typename T>
void CVector<T>::push_back(T value)
{
	Resizing();

	*(arr + size) = value;
	++size;
}

template<typename T>
void CVector<T>::pop_back()
{
	if (0 == size)
		return;

	--size;
}

template<typename T>  // 바깥 템플릿(컨테이너가 어떤 타입을 담을지 결정)
template <class... Args> // 안쪽 템플릿(함수가 어떤 인자를 받아 T객체를 생성할 것인지 결정)

//Args... : 여러타입의 rvalue
//Args&&... : 여러타입의 lvalue
void CVector<T>::emplace_back(Args&&...args)
{
    Resizing();
    //Placement New : 이미 할당 된 메모리에 객체를 제자리에서 생성
    //Perfact Forwarding : 전달받은 인자들을 완벽하게 전달
    new(&arr[size]) T(std::forward<Args>(args)...);
    ++size;
}

template<typename T>
template <class... Args> 
CIterator<T> CVector<T>::emplace(size_t idx, Args&&...args)
{
    // 1. 인덱스 범위 체크 (0 <= idx <= size)
    if (idx > size)
        throw std::out_of_range("emplace: index out of range");

    // 2. 공간이 부족하면 리사이즈
    Resizing();

    // 3. idx 위치 이후의 요소들을 뒤로 한 칸씩 이동
    for (size_t i = size; i > idx; --i)
    {
        arr[i] = std::move(arr[i - 1]);
    }

    // 4. idx 위치에 객체를 "제자리 생성" (Perfect Forwarding)
    new(&arr[idx]) T(std::forward<Args>(args)...);

    // 5. 요소 개수 증가
    ++size;

    // 6. 삽입된 위치를 가리키는 iterator 반환
    return CIterator<T>(&arr[idx]);
}
template<typename T> CIterator<T> CVector<T>::insert(size_t idx, const T& value){}
template<typename T> CIterator<T> CVector<T>::erase(size_t idx){}
template<typename T> void CVector<T>::vdelete(const T& value){}
template<typename T> void CVector<T>::clear(){}
template<typename T> CIterator<T> CVector<T>::begin(){}
template<typename T> CIterator<T> CVector<T>::end(){}
template<typename T> T& CVector<T>::at(size_t idx){}
template<typename T> const T& CVector<T>::at(size_t idx) const{}
template<typename T> T& CVector<T>::front(){}
template<typename T> const T& CVector<T>::front() const{}
template<typename T> T& CVector<T>::back(){}
template<typename T> const T& CVector<T>::back() const{}
template<typename T> bool CVector<T>::contains(const T& value){} 