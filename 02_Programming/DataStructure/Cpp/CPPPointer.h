#include <cstddef> // size_t
#include <utility> // std::forward

template<typename T>
class CUniquePtr
{
public:
	explicit CUniquePtr(T* p = nullptr)
		: ptr(p) 
	{
	}

	~CUniquePtr()
	{
		delete ptr; 
	}

	// copy prohibition
	CUniquePtr(const CUniquePtr&) = delete;
	CUniquePtr& operator=(const CUniquePtr&) = delete;

	// move
	CUniquePtr(CUniquePtr&& other) noexcept
		:ptr(other.ptr)
	{
		other.ptr = nullptr;
	}

	CUniquePtr& operator=(CUniquePtr&& other) noexcept
	{
		if (this != &other)
		{
			delete ptr;
			ptr = other.ptr;
			other.ptr = nullptr;
		}
		return *this;
	}
	
	T* operator->() const { return ptr; }
	T& operator*() const { return *ptr; }

private:
	T* ptr;
};

template<typename T, typename... Args>
CUniquePtr<T> CMakeUnique(Args&&... args)
{
	return CUniquePtr<T>(new T(std::forward<Args>(args)...));
}

template<typename T>
struct CControlBlock
{
	T* ptr;
	size_t useCount;
	size_t weakCount;

	CControlBlock(T* p)
		: ptr(p), useCount(1), weakCount(0)
	{
	}
};

/*
template<typename T>
class CSharedPtr
{
public:
	explicit CSharedPtr(T* p = nullptr)
		: ptr(p), refCount(new size_t(1))
	{
	}

	~CSharedPtr()
	{
		Release();
	}

	CSharedPtr(const CSharedPtr& other)
		: ptr(other.ptr), refCount(other.refCount)
	{
		++(*refCount);
	}

	CSharedPtr& operator=(const CSharedPtr& other)
	{
		if (this != &other)
		{
			Release();
			ptr = other.ptr;
			refCount = other.refCount;
			++(*refCount);
		}
		return *this;
	}

	CSharedPtr(CSharedPtr&& other) noexcept
		: ptr(other.ptr), refCount(other.refCount)
	{
		other.ptr = nullptr;
		other.refCount = nullptr;
	}

	CSharedPtr& operator=(CSharedPtr&& other) noexcept
	{
		if (this != &other)
		{
			Release();
			ptr = other.ptr;
			refCount = other.refCount;
			other.ptr = nullptr;
			other.refCount = nullptr;
		}
		return *this;
	}

	T* operator->() const { return ptr; }
	T& operator*() const { return *ptr; }

private:
	T* ptr;
	size_t* refCount;	// 복사된 shared_ptr끼리 카운트를 공유해야 함
						// 두 객체가 동일한 카운터를 사용
private:
	void Release()
	{
		if (refCount)
		{
			if (--(*refCount) == 0)
			{
				delete ptr;
				delete refCount;
			}

			refCount = nullptr;
			ptr = nullptr;
		}
	}

public:
	size_t Count() const { return refCount ? *refCount : 0; }
};
*/

template<typename T>
class CWeakPtr; // Forward declaration

template<typename T>
class CSharedPtr
{
	friend class CWeakPtr<T>;

public:
	CSharedPtr()
		: ctr(nullptr)
	{
	}

	explicit CSharedPtr(T* p)
		: ctr(new CControlBlock<T>(p))
	{
	}

	~CSharedPtr()
	{
		Release();
	}

	// Copy
	CSharedPtr(const CSharedPtr& other)
		: ctr(other.ctr)
	{
		if (ctr)
			++ctr->useCount;
	}

	CSharedPtr& operator=(const CSharedPtr& other)
	{
		if (this != &other)
		{
			Release();
			ctr = other.ctr;
			if (ctr)
				++ctr->useCount;
		}
		return *this;
	}

	// Move
	// 선택적 구현(원본 포인터의 nullptr 초기화를 위함)
	CSharedPtr(CSharedPtr&& other) noexcept
		: ctr(other.ctr)
	{
		other.ctr = nullptr;
	}

	CSharedPtr& operator=(CSharedPtr&& other) noexcept
	{
		if (this != &other)
		{
			Release();
			ctr = other.ctr;
			other.ctr = nullptr;
		}
		return *this;
	}

	T* operator->() const { return ctr ? ctr->ptr : nullptr; }
	T& operator*() const { return *(ctr->ptr); }

private:
	CControlBlock<T>* ctr;

private:
	void Release()
	{
		if (ctr)
		{
			if (--ctr->useCount == 0)
			{
				delete ctr->ptr;
				ctr->ptr = nullptr;

				if (ctr->weakCount == 0)
				{
					delete ctr;
					ctr = nullptr;
					return;
				}
			}
			ctr = nullptr;
		}
	}

public:
	size_t use_count() const { return ctr ? ctr->useCount : 0; }
	bool expired() const { return !ctr || ctr->useCount == 0; }
};

template<typename T, typename... Args>
CSharedPtr<T> CMakeShared(Args&&... args)
{
	return CSharedPtr<T>(new T(std::forward<Args>(args)...));
}

template<typename T>
class CWeakPtr
{
	friend class CSharedPtr<T>;

public:
	CWeakPtr()
		: ctr(nullptr)
	{
	}

	~CWeakPtr()
	{
		Release();
	}

	CWeakPtr(const CSharedPtr<T>& shared)
		: ctr(shared.ctr)
	{
		if (ctr)
			++ctr->weakCount;
	}

	CWeakPtr(const CWeakPtr& other)
		: ctr(other.ctr)
	{
		if (ctr)
			++ctr->weakCount;
	}

	CWeakPtr& operator=(const CWeakPtr& other)
	{
		if (this != &other)
		{
			Release();
			ctr = other.ctr;
			if (ctr)
				++ctr->weakCount;
		}
		return *this;
	}
	
	/*
	// 소유권 문제가 없음
	// 이동이 발생하더라도 실질적으로 해제할 리소스는 없음
	CWeakPtr(CWeakPtr&& other) noexcept
		: ctr(other.ctr)
	{
		other.ctr = nullptr;
	}

	CWeakPtr& operator=(CWeakPtr&& other) noexcept
	{
		if (this != &other)
		{
			Release();
			ctr = other.ctr;
			other.ctr = nullptr;
		}
		return *this;
	}
	*/

private:
	CControlBlock<T>* ctr;

private:
	void Release()
	{
		if (ctr)
		{
			if (--ctr->weakCount == 0 && ctr->useCount == 0)
				delete ctr;

			ctr = nullptr;
		}
	}

	bool expired() const
	{
		return !ctr || ctr->useCount == 0;
	}

	CSharedPtr<T> lock() const
	{
		if (ctr && ctr->useCount > 0)
			return CSharedPtr<T>(*this);

		return CSharedPtr<T>();
	}
};
