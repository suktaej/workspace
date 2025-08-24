#include "CPPIterator.h"
#include <type_traits>

class CStd
{
    template<typename T>
    typename std::remove_reference<T>::type&& move(T&& arg) noexcept
    {
        return static_cast<typename std::remove_reference<T>::type&&>(arg);
    }

    // C++14 이상에서 _t 헬퍼 사용가능
    template<typename T>
    std::remove_reference_t<T>&& move_cpp14(T&& arg) noexcept
    {
        return static_cast<std::remove_reference_t<T>&&>(arg);
    }

    template<typename inputIter, typename T>
    inputIter find(inputIter first, inputIter last, const T& value)
    {
        // first부터 last에 도달하기 전까지 순회
        while(first != last)
        {
            // 현재 이터레이터가 가리키는 값(*first)과 찾으려는 값(value)을 비교
            if (*first == value)
            {
                // 값을 찾았으면 현재 이터레이터를 반환
                return first;
            }
            ++first;
        }

        // 루프가 끝날 때까지 값을 찾지 못했다면, 범위의 끝(last)을 반환
        return last;
    }
};