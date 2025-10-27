#pragma once
#include <type_traits>
#include <cstdint>
#include <cstring> // for memcpy
#include <string>

template<typename T>
struct CHash
{
    /*  // C++ 20
    size_t operator()(const T& key, size_t bucketCount) const
        requires std::is_arithmetic_v<T>  
    */
	template<typename U = T>
	typename std::enable_if<std::is_arithmetic<U>::value, size_t>::type
		operator()(const T& key, size_t bucketCount) const
	{
		uint64_t bits = 0;
		std::memcpy(&bits, &key, sizeof(T)); // sizeof(bits) >= sizeof(T)

		bits ^= (bits >> 33);
		bits *= 0xff51afd7ed558ccdULL;
		bits ^= (bits >> 33);
		bits *= 0xc4ceb9fe1a85ec53ULL;
		bits ^= (bits >> 33);

		return static_cast<size_t>(bits % bucketCount);
	}
};

/*
template<>
struct CHash<int>
{
    size_t operator()(int key, size_t bucketCount) const 
    {
        key ^= (key >> 16);
        key *= 0x45d9f3b;
        key ^= (key >> 16);
       
        return key % bucketCount;
    }
};
*/

template<>
struct CHash<std::string>
{
    size_t operator()(const std::string& key, size_t bucketCount) const 
    {
        if (bucketCount == 0)
            return 0;

        size_t hash = 1469598103934665603ULL; // FNV-1a
   
        for (char c : key) {
            hash ^= (unsigned char)c;
            hash *= 1099511628211ULL;
        }
       
        return hash % bucketCount;
    }
};

template<typename T>
constexpr T rotate_right(T value, unsigned int shift)
{
    constexpr unsigned int bitCount = sizeof(T) * 8;
    shift %= bitCount; // 0~63 범위로 제한

    return (value >> shift) | (value << (bitCount - shift));
}

template<typename T>
constexpr T rotate_left(T value, unsigned int shift)
{
    constexpr unsigned int bitCount = sizeof(T) * 8;
    shift %= bitCount;

    return (value << shift) | (value >> (bitCount - shift));
}