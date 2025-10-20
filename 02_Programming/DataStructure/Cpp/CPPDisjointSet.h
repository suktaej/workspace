#include "CPPVector.h"

class CDisjointSet
{
public:
	explicit CDisjointSet(size_t _inp = 0)
		: parent(_inp), rank(_inp, 0)
	{
		for (size_t i = 0;i < _inp;++i)
			parent[i] = i;
	}

	void Resize(size_t _inp)
	{
		parent.resize(_inp);
		rank.resize(_inp,0);

		for (size_t i = 0; i < _inp; ++i)
			parent[i] = i;
	}

	size_t Find(size_t _find)
	{
		if (parent[_find] != _find)
			parent[_find] = Find(parent[_find]);	// 경로압축 (Path Compression)

		return parent[_find];
	}

	bool Union(size_t x, size_t y)
	{
		x = Find(x);
		y = Find(y);

		if (x == y)
			return false;

		if (rank[x] < rank[y])
			parent[x] = y;
		else if (rank[x] > rank[y])
			parent[y] = x;
		else
		{
			parent[y] = x;
			rank[x]++;
		}

		return true;
	}

	bool Connected(size_t x, size_t y)
	{
		return Find(x) == Find(y);
	}

private:
	CVector<size_t> parent; // Node i의 parentNode index
							// Node와 parent가 같은 값일 경우 자기 자신이 루트(대표노드)
	CVector<size_t> rank;	// Node i가 root일 경우 tree의 높이
};