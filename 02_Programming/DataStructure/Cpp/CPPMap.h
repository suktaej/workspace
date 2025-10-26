#include "CPPTree.h"
#include <functional>

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
	struct CMapIterator
	{
		TreeNode<MapNode<K,V>>* current;
		CMap* container;

		CMapIterator(TreeNode<MapNode<K,V>>* node, CMap* map) 
			: current(node), container(map)
		{}

		MapNode<K,V>& operator*() { return current->data; }
        MapNode<K,V>* operator->() { return &(current->data); }
        CMapIterator& operator++() 
		{
            current = container->nextInOrder(current);
            return *this;
        }
		CMapIterator operator++(int) 
        {
            CMapIterator temp = *this;
            current = container->nextInOrder(current);
            return temp;
        }
		CMapIterator& operator--() 
		{
            current = container->prevInOrder(current);
            return *this;
        }
		CMapIterator operator--(int) 
        {
            CMapIterator temp = *this;
            current = container->prevInOrder(current);
            return temp;
        }

        bool operator!=(const CMapIterator& other) const 
		{
            return current != other.current;
        }
	};

	CMapIterator begin() { return CMapIterator(leftmost(this->root)); }
    CMapIterator end() { return CMapIterator(nullptr); }

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
	bool contains(const K& key) const; 

	V& operator[](const K& key) 
	{
		auto node = FindNode(key);
		if (node)
			return node->value;

		this->insert(key, V{});

		return FindNode(key)->value;
	}

private:
	MapNode<K,V>* FindNode(const K& key);
	TreeNode<MapNode<K,V>>* nextInOrder(TreeNode<MapNode<K,V>>* node)
	{
		if (!node) return nullptr;

		// 1. 오른쪽 자식이 있으면, 오른쪽 서브트리의 가장 왼쪽 노드
		if (node->right)
		{
			node = node->right;
			while (node->left) node = node->left;
			return node;
		}

		// 2. 오른쪽 자식이 없으면, 부모를 따라 올라가면서 자신이 왼쪽 자식인 경우
		TreeNode<MapNode<K,V>>* parent = node->parent;
		while (parent && node == parent->right)
		{
			node = parent;
			parent = parent->parent;
		}
		return parent;
	}
	
	TreeNode<MapNode<K,V>>* prevInOrder(TreeNode<MapNode<K,V>>* node)
	{
		if (!node) return nullptr;
	
		// 왼쪽 서브트리가 있으면 가장 오른쪽 노드
		if (node->left) {
			node = node->left;
			while (node->right) node = node->right;
			return node;
		}
	
		// 왼쪽 서브트리가 없으면 부모를 따라 올라가기
		TreeNode<MapNode<K,V>>* parent = node->parent;
		while (parent && node == parent->left) {
			node = parent;
			parent = parent->parent;
		}
		return parent;
	}

	TreeNode<MapNode<K,V>>* leftmost(TreeNode<MapNode<K,V>>* node)
    {
        if (!node) return nullptr;
        while (node->left) node = node->left;
        return node;
    }
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

template<typename K, typename V>
inline bool CMap<K, V>::contains(const K& key) const
{
	return FindNode(key) != nullptr;
}