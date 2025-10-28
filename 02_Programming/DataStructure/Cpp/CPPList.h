#pragma once
#include <cstddef>
#include <utility>
#include <initializer_list>
#include <stdexcept>

template<typename T>
class CList
{
private:
	struct Node
	{
		T data;
		Node* prev;
		Node* next;
		// std::forward : 템플릿 함수 안에서 인자는 이름을 갖는 순간 모두 lvalue화
		// forward는 lvalue일 경우 lvalue의 참조값으로 변환하여 복사를
		// ravlue일 경우 rvalue의 참조값으로 변환하여 이동을 지원

		// std::move의 경우 무조건 rvalue로 변환(강제형변환)	
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
			if (currentNode == nullptr)
				throw std::out_of_range("operator++ : iterator at end");

			currentNode = currentNode->next;
			return *this;
		}
		iter operator++(int)
		{
			iter temp = *this;
			++(*this);
			return temp;
		}
		iter& operator--()
		{
			if (currentNode == nullptr)
				throw std::out_of_range("operator-- : iterator at begin");

			if (currentNode->prev == nullptr) // CList의 begin()에서 감소 시도
				throw std::out_of_range("CListIterator::operator-- : iterator at begin");

			currentNode = currentNode->prev;
			return *this;
		}
		iter operator--(int)
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
	iter begin() { return iter(mHead); }
	iter end() const { return iter(nullptr); }
	iter end() { return iter(nullptr); }
	size_t size() const { return mSize; }
	bool empty() const { return 0 == mSize; }
	iter back_iterator() { return iter(mTail); }
    const iter back_iterator() const { return iter(mTail); }

	T& back()
	{
		if (nullptr == mTail)
			throw std::out_of_range("back : empty list");

		return mTail->data;
	}
	
	const T& back() const
	{
		if (nullptr == mTail)
			throw std::out_of_range("back : empty list");

		return mTail->data;
	}
	
	T& front()
	{
		if (nullptr == mHead)
			throw std::out_of_range("front : empty list");

		return mHead->data;
	}
	
	const T& front() const
	{
		if (nullptr == mHead)
			throw std::out_of_range("front : empty list");

		return mHead->data;
	}

	template<class... Args>
	void push_front(Args&&... args)
	{
		Node* newNode = new Node(std::forward<Args>(args)...);

		// 처음 노드가 삽입될 경우
		if (nullptr == mHead)
			mHead = mTail = newNode;
		else
		{
			newNode->next = mHead;	// 새 Node를 Head 앞으로
			mHead->prev = newNode;	// 기존 head의 prev를 새 Node로
			mHead = newNode;		// head 갱신
		}

		++mSize;
	}

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
			throw std::out_of_range("pop_back : empty list");

		Node* popNode = mTail;
		mTail = mTail->prev;

		if (nullptr != mTail)
			mTail->next = nullptr;
		else
			mHead = nullptr;

		delete popNode;
		
		--mSize;
	}

	void pop_front()
	{
		if (nullptr == mHead)
			throw std::out_of_range("pop_front : empty list");

		Node* popNode = mHead;
		mHead = mHead->next;

		if (nullptr != mHead)
			mHead->prev = nullptr;
		else
			mTail = nullptr;

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

