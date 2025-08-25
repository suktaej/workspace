#pragma once
#include <cstddef>
#include <utility>

template<typename T>
class CList
{
private:
	struct Node
	{
		T data;
		Node* prev;
		Node* next;
		
		template<class... Args>
		explicit Node(Args&&... args) : data(std::forward<Args>(args)...), prev(nullptr), next(nullptr) {}
	};

public:
	class CListIterator
	{
	public:
		using iter = CListIterator;

	public:
		CListIterator() : currentNode(nullptr) {}
		explicit CListIterator(Node* _node) : currentNode(_node) {}

	private: 
		Node* currentNode;
		
	public:
		T& operator*() const { return currentNode->data; }
		T* operator->() const { return &currentNode->data; }
		iter& operator++() 
		{
			currentNode = currentNode->next;
			return *this;
		}
		iter& operator++(int)
		{
			iter temp = *this;
			++(*this);
			return temp;
		}
		iter& operator--()
		{
			currentNode = currentNode->prev;
			return *this;
		}
		iter& operator--(int)
		{
			iter temp = *this;
			--(*this);
			return temp;
		}
		bool operator==(const iter& it) const { return currentNode == it.currentNode; }
		bool operator!=(const iter& it) const { return currentNode != it.currentNode; }
		Node* node() const { return currentNode; }

	};

public:
	CList() : mHead(nullptr), mTail(nullptr), mSize(0) {}
	CList(const CList& _list)
		: mHead(nullptr), mTail(nullptr), mSize(0) 
	{
		for (Node* node = _list.mHead; node != nullptr; node = node->next)
			push_back(node->data);
	}
	CList& operator=(const CList& _list)
	{
		if (this != &_list)
		{
			clear();

			for (Node* node = _list.mHead; node != nullptr; node = node->next)
				push_back(node->data);
		}

		return *this;
	}
	CList(CList&& _list) noexcept
		: mHead(_list.mHead), mTail(_list.mTail),mSize(_list.mSize)
	{
		_list.mHead = nullptr;
		_list.mTail = nullptr;
		_list.mSize = 0;
	}
	CList& operator=(CList&& _list) noexcept
	{
		if (this != &_list)
		{
			clear();
			mHead = _list.mHead;
			mTail = _list.mTail;
			mSize = _list.mSize;

			_list.mHead = nullptr;
			_list.mTail = nullptr;
			_list.mSize = 0;
		}

		return *this;
	}
	~CList()
	{
		Node* currentNode = mHead;
		while (currentNode != nullptr)
		{
			Node* nextNode = currentNode->next;
			delete currentNode;
			currentNode = nextNode;
		}
	}

private:
	Node* mHead;
	Node* mTail;
	size_t mSize;

public:
	using iter = CListIterator;

public:
	iter begin() const { return iter(mHead); }
	iter end() const { return iter(nullptr); }
	size_t size() const { return mSize; }
	bool empty() const { return 0 == mSize; }

	template<class... Args>
	void push_back(Args&&... args) 
	{
		Node* newNode = new Node(std::forward<Args>(args)...);

		// 처음 노드가 삽입될 경우
		if (nullptr == mTail)
			mHead = mTail = newNode;
		else
		{
			// 두 번째 노드 삽입 시, mHead와 mTail은 같은 노드를 가리키고 있음
			// 때문에 mHead의 next 또한 newNode를 가르킴
			mTail->next = newNode;
			newNode->prev = mTail;
			mTail = newNode;
		}

		++mSize;
	}

	void pop_back()
	{
		if (nullptr == mTail)
			return;

		Node* popNode = mTail;
		mTail = mTail->prev;

		if (nullptr != mTail)
			mTail->next = nullptr;
		else
			mHead = nullptr;

		delete popNode;
		
		--mSize;
	}

	void clear()
	{
		Node* currentNode = mHead;

		while (nullptr != currentNode)
		{
			Node* nextNode = currentNode->next;
			delete currentNode;
			currentNode = nextNode;
		}

		mHead = mTail = nullptr;
		mSize = 0;
	}

	template<class... Args>
	iter insert(iter _pos, Args&&... args)
	{
		// iterator(list)에 Node가 존재하지 않는다면
		if (nullptr == _pos.node())
		{
			push_back(std::forward<Args>(args)...);
			return iter(mTail);
		}

		Node* posNode = _pos.node();
		Node* newNode = new Node(std::forward<Args>(args)...);
		Node* prevNode = posNode->prev;

		newNode->next = posNode;
		newNode->prev = prevNode;

		posNode->prev = newNode;
		
		// 첫번째 Node였을 경우
		if (nullptr == prevNode)
			mHead = newNode;
		else
			prevNode->next = newNode;

		++mSize;
		return iter(newNode);
	}

	iter erase(iter _pos)
	{
		Node* posNode = _pos.node();

		if (nullptr == posNode)
			return end();

		Node* prevNode = posNode->prev;
		Node* nextNode = posNode->next;

		if (nullptr == prevNode)
			mHead = nextNode;
		else
			prevNode->next = nextNode;

		if (nullptr == nextNode)
			mTail = prevNode;
		else
			nextNode->prev = prevNode;

		delete posNode;
		--mSize;
		return iter(nextNode);
	}
};

