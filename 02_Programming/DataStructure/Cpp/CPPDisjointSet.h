#include "CPPVector.h"

class CDisjointSet
{
public:
	explicit CDisjointSet(size_t _inp = 0)
		: parent(_inp), rank(_n, 0)
	{
		for (size_t i = 0;i < _inp;++i)
			parent[i] = i;
	}

	void Resize(size_t _inp)
	{
		parent.resize(_inp);
		rank.resize(_inp, 0);

		for (size_t i = 0; i < _inp; ++i)
			parent[i] = i;
	}

	size_t Find(size_t _find)
	{
		if (parent[_find] != _find)
			parent[_find] = Find(parent[_find]);	// ��ξ��� (Path Compression)

		return parent[_find];
	}

	bool Union(size_t x, size_t y)
	{
		x = Find(x);
		y = Find(y);

		if (x == y)
			return false;

		if (rank[x] < rank[y])
			parnet[x] = y;
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
	CVector<size_t> parent; // Node i�� parentNode index
							// Node�� parent�� ���� ���� ��� �ڱ� �ڽ��� ��Ʈ(��ǥ���)
	CVector<size_t> rank;	// Node i�� root�� ��� tree�� ����
};