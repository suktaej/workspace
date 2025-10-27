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
    explicit CHashMap(size_t _bucketCount = 16)
        : buckets(_bucketCount), bucketCount(_bucketCount), elementCount(0) { }
    ~CHashMap() = default;

private:
    CVector<CList<std::pair<K, V>>> buckets;    //Separate Chaining
    size_t bucketCount;
    size_t elementCount;
    CHash<K> hasher;
    float loadFactor = 0.75f;

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
