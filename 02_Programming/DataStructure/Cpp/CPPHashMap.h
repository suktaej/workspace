#pragma once
#include "CPPVector.h"
#include "CPPList.h"
#include "CPPHash.h" 
#include <utility>  // for std::pair
#include <optional> // for std::optional
#include <stdexcept>

template<typename K, typename V>
class CHashMap
{
public:
    struct HashIterator
    {
        CHashMap* parent;
        size_t bucketIndex;
        typename CList<std::pair<K, V>>::CListIterator iter;

        HashIterator(CHashMap* map, size_t idx, typename CList<std::pair<K, V>>::CListIterator it)
            : parent(map), bucketIndex(idx), iter(it) {}

        std::pair<K, V>& operator*() { return *iter; }
        std::pair<K, V>* operator->() { return &(*iter); }

        HashIterator& operator++()
        {
            if (bucketIndex == parent->bucketCount) { // 이미 end() 상태이면 예외 대신 그냥 반환하거나, 다음 동작 없음
                return *this;
            }

            ++iter; // 현재 버킷의 다음 요소로 이동

            // 현재 버킷의 끝에 도달했다면, 다음 비어있지 않은 버킷을 찾는다.
            while (iter == parent->buckets[bucketIndex].end())
            {
                ++bucketIndex; // 다음 버킷으로 이동

                // 모든 버킷을 다 탐색했다면, end() 상태로 만든다.
                if (bucketIndex == parent->bucketCount)
                {
                    iter = typename CList<std::pair<K, V>>::CListIterator(nullptr); // end() iterator의 Node*는 nullptr
                    break; // 루프 종료
                }
                else // 다음 버킷으로 이동했다면, 해당 버킷의 begin()으로 iter 설정
                {
                    iter = parent->buckets[bucketIndex].begin();
                }
            }
            return *this;
        }

        HashIterator operator++(int)
        {
            HashIterator temp = *this;
            ++(*this);
            return temp;
        }

        HashIterator& operator--()
        {
            if (parent->elementCount == 0)
                throw std::out_of_range("operator--: empty map, cannot decrement");

            // 현재 이터레이터가 CHashMap::end() 상태인 경우
            if (bucketIndex == parent->bucketCount)
            {
                size_t currentBucket = parent->bucketCount;
                while (currentBucket > 0 && parent->buckets[currentBucket - 1].empty())
                    --currentBucket;

                if (currentBucket == 0) // 모든 버킷이 비었거나 begin()보다 앞
                    throw std::out_of_range("operator--: cannot decrement past begin (empty map or no elements)");

                bucketIndex = currentBucket - 1; // 마지막 비어있지 않은 버킷으로 이동
                iter = parent->buckets[bucketIndex].back_iterator(); // <--- CList의 마지막 요소로 직접 이동!
                return *this;
            }

            // 현재 CList 내에서 이동하는 경우
            // CList::CListIterator의 begin()이 아닌 경우
            if (iter != parent->buckets[bucketIndex].begin())
            {
                --iter; // CList::CListIterator::operator--가 호출됨
                return *this;
            }

            // 현재 CList의 begin()인 경우, 이전 비어있지 않은 버킷을 찾는다
            size_t currentBucket = bucketIndex;
            while (currentBucket > 0)
            {
                --currentBucket;
                if (!parent->buckets[currentBucket].empty())
                {
                    bucketIndex = currentBucket;
                    iter = parent->buckets[bucketIndex].back_iterator(); // <--- CList의 마지막 요소로 직접 이동!
                    return *this;
                }
            }

            throw std::out_of_range("operator--: cannot decrement past begin");
        }

        HashIterator operator--(int)
        {
            HashIterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const HashIterator& other) const
        {
            // 둘 다 end() 상태인 경우
            if (bucketIndex == parent->bucketCount && other.bucketIndex == parent->bucketCount)
                return true;
            // 둘 중 하나만 end() 상태인 경우
            if (bucketIndex == parent->bucketCount || other.bucketIndex == parent->bucketCount)
                return false;
            // 둘 다 유효한 요소를 가리키는 경우
            return parent == other.parent &&
                   bucketIndex == other.bucketIndex &&
                   iter == other.iter;
        }

        bool operator!=(const HashIterator& other) const
        {
            return !(*this == other);
        }
    };

    HashIterator begin()
    {
        for (size_t i = 0; i < bucketCount; ++i)
        {
            if (!buckets[i].empty())
                return HashIterator(this, i, buckets[i].begin());
        }

        return end();
    }

    HashIterator end()
    {
        return HashIterator(this, bucketCount, typename CList<std::pair<K, V>>::CListIterator(nullptr));
    }

private:
    CVector<CList<std::pair<K, V>>> buckets;    //Separate Chaining
    size_t bucketCount;
    size_t elementCount;
    CHash<K> hasher;
    float loadFactor = 0.75f;

public:
    explicit CHashMap(size_t _bucketCount = 16)
        : buckets(_bucketCount), bucketCount(_bucketCount), elementCount(0) { }
    
    // Copy Constructor
    CHashMap(const CHashMap& other)
        : buckets(other.bucketCount), bucketCount(other.bucketCount), elementCount(other.elementCount), hasher(other.hasher), loadFactor(other.loadFactor)
    {
        for (size_t i = 0; i < bucketCount; ++i)
            buckets[i] = other.buckets[i]; // CList 복사
    }

    // Copy Assignment
    CHashMap& operator=(const CHashMap& other)
    {
        if (this == &other)
            return *this;

        bucketCount = other.bucketCount;
        elementCount = other.elementCount;
        hasher = other.hasher;
        loadFactor = other.loadFactor;

        buckets.resize(bucketCount);

        for (size_t i = 0; i < bucketCount; ++i)
            buckets[i] = other.buckets[i]; // CList 복사

        return *this;
    }

    // Move Constructor
    CHashMap(CHashMap&& other) noexcept
        : buckets(std::move(other.buckets)), bucketCount(other.bucketCount), elementCount(other.elementCount), hasher(std::move(other.hasher)), loadFactor(other.loadFactor)
    {
        other.bucketCount = 0;
        other.elementCount = 0;
    }

    // Move Assignment
    CHashMap& operator=(CHashMap&& other) noexcept
    {
        if (this == &other)
            return *this;

        buckets = std::move(other.buckets);
        bucketCount = other.bucketCount;
        elementCount = other.elementCount;
        hasher = std::move(other.hasher);
        loadFactor = other.loadFactor;

        other.bucketCount = 0;
        other.elementCount = 0;

        return *this;
    }

    ~CHashMap() = default;

public:
    void insert(const K& key, const V& value)
    {
        size_t index = hasher(key, bucketCount);
        CList<std::pair<K, V>>& bucket = buckets[index];

        // 존재하는 key인지 탐색
        for (auto it = bucket.begin(); it != bucket.end(); ++it)
        {
            if (it->first == key)
            {
                it->second = value; // 값 갱신
                return;
            }
        }
        
        // 존재하지 않는다면 삽입
        bucket.push_back(std::make_pair(key, value));
        ++elementCount;

        // Rehash
        if ((float)elementCount / bucketCount > loadFactor)
            Rehash(bucketCount * 2);
    }

    V* find(const K& key)
    {
        size_t index = hasher(key, bucketCount);
        CList<std::pair<K, V>>& bucket = buckets[index];

        for (auto it = bucket.begin(); it != bucket.end(); ++it)
        {
            if (it->first == key)
                return &(it->second);
        }

        return nullptr;
    }

    bool contains(const K& key) const
    {
        size_t index = hasher(key, bucketCount);
        const CList<std::pair<K, V>>& bucket = buckets[index];

        for (const auto& [k, _] : bucket)
        {
            if (k == key)
                return true;
        }
        return false;
    }

    bool remove(const K& key)
    {
        size_t index = hasher(key, bucketCount);
        CList<std::pair<K, V>>& bucket = buckets[index];

        for (auto it = bucket.begin(); it != bucket.end(); ++it)
        {
            if (it->first == key)
            {
                bucket.erase(it);
                --elementCount;
                return true;
            }
        }
        return false;
    }

    size_t size() const { return elementCount; }
    bool empty() const { return elementCount == 0; }

    V& operator[](const K& key)
    {
        size_t index = hasher(key, bucketCount);
        CList<std::pair<K, V>>& bucket = buckets[index];

        for (auto& [k, v] : bucket)
        {
            if (k == key)
                return v;
        }

        bucket.push_back(std::make_pair(key, V{}));
        ++elementCount;

        if ((float)elementCount / bucketCount > loadFactor)
            Rehash(bucketCount * 2);

        return bucket.back().second;
    }

private:
void Rehash(size_t newBucketCount)
	{
		CVector<CList<std::pair<K, V>>> newBuckets(newBucketCount);

		for (auto& bucket : buckets)
		{
			for (auto& [key, value] : bucket)
			{
				size_t newIndex = hasher(key, newBucketCount);
				newBuckets[newIndex].push_back(std::make_pair(key, value));
			}
		}

		buckets = std::move(newBuckets);
		bucketCount = newBucketCount;
	}
};
