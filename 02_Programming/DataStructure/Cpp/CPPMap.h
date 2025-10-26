#include "CPPTree.h"

template<typename K, typename V>
struct MapNode
{
	K key;
	V value;

	MapNode() = default;
	MapNode(const K& k, const V& v)
		: key(k), value(v) 
	{
	}

	// 정렬을 위해 key 비교
	bool operator<(const MapNode& other) const 
	{
		return key < other.key; 
	}
	bool operator>(const MapNode& other) const 
	{
		return key > other.key; 
	}
	bool operator==(const MapNode& other) const 
	{
		return key == other.key; 
	}
};

template<typename K, typename V>
class CMap : public CRedBlackTree<MapNode<K,V>> 
{
	using CRedBlackTree<MapNode<K,V>>::insert;
	using CRedBlackTree<MapNode<K,V>>::remove;	//namehiding 방지

public:
	CMap()
		: CRedBlackTree<MapNode<K, V>>()
	{
	}

	virtual ~CMap()
	{
	}

public:
	void insert(const K& key, const V& value);
	V* find(const K& key);
	void remove(const K& key);

private:
	MapNode<K,V>* FindNode(const K& key);
};

template<typename K, typename V>
inline void CMap<K, V>::insert(const K& key, const V& value)
{
	MapNode<K, V> pair(key, value);
	CRedBlackTree<MapNode<K, V>>::insert(pair);
}

template<typename K, typename V>
inline V* CMap<K, V>::find(const K& key)
{
	MapNode<K, V>* found = FindNode(key);
	return found ? &(found->value) : nullptr;
}

template<typename K, typename V>
inline void CMap<K, V>::remove(const K& key)
{
	MapNode<K, V> temp(key, V{});
	CRedBlackTree<MapNode<K, V>>::remove(temp);
}

template<typename K, typename V>
inline MapNode<K,V>* CMap<K, V>::FindNode(const K& key)
{
	TreeNode<MapNode<K,V>>* current = this->root;
	while (current)
	{
		if (key == current->data.key)
			return &(current->data);
		else if (key < current->data.key)
			current = current->left;
		else
			current = current->right;
	}
	return nullptr;
}
