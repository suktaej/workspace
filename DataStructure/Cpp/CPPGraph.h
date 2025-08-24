#include "CPPVector.h"
#include <utility>

class CGraph
{
public:
	CGraph(int vec) : mVertexCount(vec)
	{
		adjacency.resize(mVertexCount);
	}

	~CGraph()
	{
	}

private:
	int mVertexCount;
	CVector<CVector<std::pair<int, int>>> adjacency;

public:
	void Dijkstra();
	void AddEdge(int u, int v, int weight);
};