#include "CPPVector.h"
#include "CPPList.h"
#include <limits>

class CGraph
{
public:
	struct Edge
	{
		size_t to;
		int weight;
		Edge() : to(std::numeric_limits<size_t>::max()), weight(0) {}
		Edge(size_t _to, int _w) : to(_to), weight(_w) {}
	};

	struct Vertex
	{
		size_t id;
		std::string name;
		float x, y;
		CList<Edge> adjacency;
	};

public:
	explicit CGraph(size_t _vertex = 0) : mVtxCnt(_vertex), mAdj(_vertex), mDir(true) { }

	~CGraph()
	{
	}

private:
	size_t mVtxCnt;
	CVector<CList<Edge>> mAdj;
	bool mDir;

public:
	void AddVertex();
	void AddEdge(size_t _u, size_t _v, const int& _w);
	bool RemoveEdge(size_t _u, size_t _v);
	void SetDirection(bool value);

	void PrintGraph();
	void Dijkstra(const CGraph& graph, size_t start);
};