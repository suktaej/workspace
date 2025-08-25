#include "CPPVector.h"
#include "CPPList.h"
#include <utility>

class CGraph
{
public:
	struct Edge
	{
		size_t to;
		int weight;
		Edge(size_t _to, int _w) : to(_to), weight(_w) {}
	};

public:
	explicit CGraph(size_t _vertex = 0) : mVertexCount(_vertex), mAdj(_vertex), mDir(true) { }

	~CGraph()
	{
	}

private:
	size_t mVertexCount;
	CVector<CList<Edge>> mAdj;
	bool mDir;

public:
	void AddVertex();
	void AddEdge(size_t _u, size_t _v, const int& _w);
	bool RemoveEdge(size_t _u, size_t _v);
};