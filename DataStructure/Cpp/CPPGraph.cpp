#include "CPPGraph.h"
#include <vector>
#include <limits>

void CGraph::AddVertex()
{
	mAdj.emplace_back(CList<Edge>{});	// 임시객체 생성
	++mVtxCnt;
}

void CGraph::AddEdge(size_t src, size_t dest, const int& weight = 0)
{
	if (src >= mVtxCnt || dest >= mVtxCnt)
		throw std::out_of_range("add_edge : invalid vertex");

	mAdj[src].push_back(dest, weight);

	if (false == mDir)
		mAdj[dest].push_back(src, weight);
}

bool CGraph::RemoveEdge(size_t src, size_t dest)
{
	if (src >= mVtxCnt || dest >= mVtxCnt)
		return false;
	
	// vertex Source의 인접리스트를 순회
	for (CList<CGraph::Edge>::iter it = mAdj[src].begin(); it != mAdj[src].end(); ++it)
	{
		// 현재 iterator가 가리키는 edge(*it)의 Dest를  확인
		if ((*it).to == dest)
		{
			// Dest가 일치한다면 edge를 CList에서 제거
			mAdj[src].erase(it);
			return true;
		}
	}
	return false;
}

void CGraph::SetDirection(bool value)
{
	mDir = value;
}

void CGraph::PrintGraph()
{
	for (size_t u = 0; u < mVtxCnt; ++u)
	{
		std::cout << "Vertex " << u << ": ";

		for (auto it = mAdj[u].begin(); it != mAdj[u].end(); ++it)
			std::cout << "(to: " << it->to << ", weight: " << it->weight << ") ";

		std::cout << "\n";
	}
}

void CGraph::Dijkstra(const CGraph& graph, size_t start)
{
	CVector<int> dist(mVtxCnt);
	
	for (int i = 0; i < mVtxCnt; ++i)
		dist.emplace_back(std::numeric_limits<int>::max());

	dist[start] = 0;
}

